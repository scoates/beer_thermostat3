#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus

#include <HardwareSerial.h>
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)

#else

void DEBUG_PRINT(char*);
void DEBUG_PRINTLN(char*);

#endif

#endif
// vim: ff=unix filetype=cpp ts=4 noet sw=4
