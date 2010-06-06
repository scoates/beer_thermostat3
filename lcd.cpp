#include "lcd.h"

#include <string.h>
#include <wiring.h>

#include "debug.h"

Lcd lcd_init(uint8_t pin)
{
	Lcd lcd;

	lcd.pin = pin;
	pinMode(lcd.pin, OUTPUT);

	lcd.device = &SoftwareSerial(-1, lcd.pin);

	lcd.device->begin(9600);
	// wait for things to settle
	delay(100);
	// must be 4 X 20 for big number format
	lcd.device->print("?G420");
	// wait for LCD #117 EEPROM to program
	delay(100);
	// turn cursor off
	lcd.device->print("?c0");
	delay(100);
	// set backlight intensity
	lcd.device->print("?B40");
	delay(100);
	// output:
	lcd.device->print("Sean's Kegerator");

	return lcd;
};

void lcd_show(Lcd *lcd, char name[], unsigned int temp, uint8_t status)
{
	unsigned int whole;

	// cursor reset (?)
	lcd->device->print("?y0?x00");
	delay(100);
	// set big character mode
	lcd->device->print("?>3");
	// allow time for the special characters to be downloaded
	delay(200);

	// note: temp is x10; so 22.3C would actually be 223
	if (temp < 100) {
		// left pad with a zero
		lcd->device->print("0");
	}
	whole = (unsigned int) (temp / 10);
	lcd->device->print(whole); // 4-wide
	lcd->device->print("."); // 2-wide
	lcd->device->print(temp - (whole * 10)); // 4-wide

	// small characters
	lcd->device->print("?<");
	delay(100);

	// position to the right of the digits
	lcd->device->print("?y0?x14");
	delay(100);

	lcd->device->print(name);

	// next line to the right of the digits
	lcd->device->print("?y1?x14");
	delay(100);

	switch (status) {
		case 0:
			lcd->device->print("OFF ");
		break;
		case 1:
			lcd->device->print("HEAT");
		break;
		case 2:
			lcd->device->print("COOL");
		break;
	}

	// next line to the right of the digits
	lcd->device->print("?y3?x14");
	delay(100);

	lcd->device->print("deg C");
};
