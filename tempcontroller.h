#ifndef TEMPCONTROLLER_H
#define TEMPCONTROLLER_H

#include <stdint.h>
#include "WProgram.h"

// special indicator that we want to measure the bandgap
// see http://www.ladyada.net/learn/sensors/tmp36.html
#define BANDGAPREF 14

typedef struct
{
	uint8_t sensor_pin;
	uint8_t cool_pin;
	uint8_t heat_pin;
	uint8_t eeprom_low;
	uint8_t eeprom_high;
	char name[4];
} Tempcontroller;

Tempcontroller tc_init(uint8_t, uint8_t, uint8_t, char *, uint8_t, uint8_t);

void tc_check_temp(Tempcontroller*);


#endif
// vim: ff=unix filetype=cpp ts=4 noet sw=4
