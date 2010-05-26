#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Ethernet.h>

class Webserver {
	uint8_t mac[6];
	uint8_t ip[4];
	Server Myserver;
	bool is_get(char[]);
	bool fast_forward(Client Browser);

	public:
	Webserver();
	void check_request();
};

#endif
// vim: ff=unix filetype=cpp ts=4 noet sw=4
