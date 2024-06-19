#include "server.h"


int main()
{
	TCPServer server(12345, "sensor_data.txt");
	server.run();
	return 0;
}
