#ifndef LCD_H
#define LCD_H

#include <SoftwareSerial.h>
#include <stdint.h>

#define BEER_LCD_UPDATE_DELTA 10000

typedef struct
{
	uint8_t pin;
	uint8_t last_update_time;
	SoftwareSerial *device;
} Lcd;

Lcd lcd_init(uint8_t pin);
void show(Lcd*, char*, uint8_t, uint8_t);

#endif
