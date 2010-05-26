#ifndef DEBUG_H
#define DEBUG_H


#ifdef __cplusplus
	#include <HardwareSerial.h>
	extern HardwareSerial Serial;
#endif

extern "C" void debug_print(char *);

#endif
// vim: ff=unix filetype=cpp ts=4 noet sw=4
