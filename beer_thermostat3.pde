/*
 * Beer Thermostat; rewrite for v3
 * Copyright (c) 2007-2010 Sean Coates (http://seancoates.com/)
 *
 * vim: ff=unix filetype=cpp ts=4 noet sw=4
 */

#define VERSION_MAJ 3
#define VERSION_MIN 0

#include "webserver.h"

#include "tempcontroller.h"

Webserver ws;
Tempcontroller tc_kegerator;
Tempcontroller tc_fermenter;

/*
 * Webserver
 * Lcd
 * Temp Sensor(s)
 * Relay(s)
 * Timer
 */

void setup()
{
	/* Keg pins: a5=sensor, d4=cool, no heat */
	tc_kegerator = tc_init(5, 4, NULL, "KEG", 0x1, 0x2);

	/* Fermenter pins: a4=sensor, d3=cool, d2=heat */
	tc_kegerator = tc_init(4, 3, 2, "FER", 0x3, 0x4);

	ws = Webserver();
	Serial.begin(9600);
}

void loop()
{
	ws.check_request();
	tc_check_temp(&tc_kegerator);

	delay(1000);
	Serial.println("looping");
}

extern "C" void __cxa_pure_virtual() {}

