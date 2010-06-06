#ifndef DEBUG_H
#define DEBUG_H

#include <HardwareSerial.h>

#define DEBUG_PRINT(s) Serial.print(s)
#define DEBUG_PRINTLN(s) Serial.println(s)
#define DEBUG_FPRINT(s,f) Serial.print(s,f)
#define DEBUG_FPRINTLN(s,f) Serial.println(s,f)

#endif
// vim: ff=unix filetype=cpp ts=4 noet sw=4
