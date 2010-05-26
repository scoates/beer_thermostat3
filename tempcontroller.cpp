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
	DEBUG_PRINT("Checking temp: ");
	DEBUG_PRINTLN(tc->name);
}

