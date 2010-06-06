#include "tempcontroller.h"
#include "debug.h"

#include <string.h>

Tempcontroller tc_init(uint8_t sensor_pin, uint8_t cool_pin, uint8_t heat_pin, char *name, uint8_t eeprom_low, uint8_t eeprom_high)
{
	Tempcontroller tc;
	tc.sensor_pin = sensor_pin;
	tc.cool_pin = cool_pin;
	tc.heat_pin = heat_pin;
	tc.eeprom_low = eeprom_low;
	tc.eeprom_high = eeprom_high;
	strcpy(tc.name, name);
	return tc;
}

void tc_check_temp(Tempcontroller *tc)
{
	// temp is 10x
	uint8_t temp;

	DEBUG_PRINT("Checking temp: ");
	DEBUG_PRINTLN(tc->name);
	DEBUG_PRINT("Pin: ");
	DEBUG_FPRINTLN(tc->sensor_pin, DEC);

	// get voltage reading from the internal 1.10V reference
	uint8_t refReading = analogRead(BANDGAPREF);

	// now calculate our power supply voltage from the known 1.05 volt reading
	float supplyvoltage = (1.10 * 1024) / refReading;

	DEBUG_PRINT("Supply voltage: ");
	DEBUG_PRINTLN(supplyvoltage);

	// read and discard the first value (to make sure the LM35 is powered)
	analogRead((int)tc->sensor_pin);
	delay(100);
	temp = analogRead(tc->sensor_pin);
	DEBUG_PRINT("Temp: ");
	DEBUG_FPRINTLN(temp, DEC);
	DEBUG_PRINT("Temp C: ");
	DEBUG_PRINTLN((5.03 * temp * 100.0)/1024.0);

	float sensorValue = 0;
	int counter;
	int sensorValues[5];
	
	for(counter = 0; counter < 4; counter++) {
		sensorValues[counter%5] = analogRead((int)tc->sensor_pin);
	}
	for(; counter < 1004; counter++) {
		sensorValues[counter%5] = analogRead((int)tc->sensor_pin);
		// find triangle smoothed value
		sensorValue += (( 
		sensorValues[(counter-2)%5] + 
		(2 * sensorValues[(counter-1)%5]) +
		(3 * sensorValues[(counter)%5]) +
		(2 * sensorValues[(counter+1)%5]) +
		sensorValues[(counter+2)%5]
		) / 9);
		
	}

	// get average of smoothed samples
	sensorValue /= 1000;
	
	// analog read is 4.9mV per point, LM35 puts out 10mV per C
	// should be 2.041
	sensorValue = (sensorValue / 2.041);

	DEBUG_PRINT("V.Temp: ");
	DEBUG_PRINTLN(sensorValue);

	//getting the voltage reading from the temperature sensor
	int reading = analogRead((int)tc->sensor_pin);

	// converting that reading to voltage
	float voltage = reading * supplyvoltage / 1024; 

	// now print out the temperature
	float temperatureC = (voltage - 0.5) * 100 ;
	// converting from 10 mv per degree wit 500 mV offset
	// to degrees ((volatge - 500mV) times 100)
	DEBUG_PRINT(temperatureC); DEBUG_PRINTLN(" degress C");

}

