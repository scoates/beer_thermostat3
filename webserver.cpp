#include "webserver.h"
#include "debug.h"

Webserver::Webserver()
	: Myserver(80)
{
	uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02 };
	uint8_t ip[] = { 192, 168, 140, 3 };
	Ethernet.begin(mac, ip);
	Myserver.begin();
}

void Webserver::check_request()
{
	Client Browser = Myserver.available();
	if (Browser) {
//		DEBUG_PRINTLN("Reading from browser.");
		char in;
		char path[3];
		int pos = 0;
		while ((in = Browser.read()) != -1) {
			// store the byte in the buffer
			path[pos++] = in;

			if (is_get(path)) {
//				DEBUG_PRINTLN("Got 'GET'");
				// reset (ugly)
				pos = path[0] = path[1] = path[2] = 0;
				
			}

//			DEBUG_PRINT("pos=");
//			DEBUG_PRINTLN(pos);

			if (pos > 2) {
//				DEBUG_PRINTLN("fast forwarding...");
//				DEBUG_PRINT(path);
				if (fast_forward(Browser)) {
//					DEBUG_PRINTLN("resetting");
					// reset (ugly)
					pos = path[0] = path[1] = path[2] = 0;
				}
			}

		}


		Myserver.write("HTTP/1.0 200 OK\nContent-type: text/html\n\n<h1>Test</h1>This is arduino!\n");
		Browser.stop();
	}
}

bool Webserver::fast_forward(Client Browser)
{
	char in;
	in = Browser.read();
	while (in != 13 && in != -1) {
		in = Browser.read();
	}
	if (13 == in) {
		// got CR, now read LF
		in = Browser.read();
	}
	return (in == 10);
}

bool Webserver::is_get(char path[])
{
	return
		path[0] == 'G'
		&& path[1] == 'E'
		&& path[2] == 'T';
}

// vim: ff=unix filetype=cpp ts=4 noet sw=4
