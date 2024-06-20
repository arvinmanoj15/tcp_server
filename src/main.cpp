#include "server.h"


// Main Function
int main()
{
	// Create TCPServer object
	TCPServer server(12345, "sensor_data.txt"); // Creating a server that will listen to port "12345" and use "sensor_data.txt" as sensor data file
	
	// Start the server
	server.run();
	
	return 0;
}
