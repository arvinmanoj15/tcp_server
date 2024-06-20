#include "server.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>


// Constructor for TCPServer
// Initializes port, file path for sensor data, and index
TCPServer::TCPServer(int port, const std::string& file_path) 
	: port(port), file_path(file_path), current_index(0) {}


// Method definition to run TCP Server
void TCPServer::run()
{
	// Loading sensor data from the file
	loadSensorData();
	
	struct sockaddr_in address; // Structure to hold the server address
	int opt = 1;
	int addrlen = sizeof(address);
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the port 12345
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	
	// Bind socket to the specified port
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	// Start listiening for incomming connections
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	
	// Server loop to accept and handle incomming client connections
	while (true)
	{
		int client_fd = acceptClient(); // Accepting connection
		if (client_fd >= 0)
		{
			handleClient(client_fd); // Handling connection
		}
	}
}


// Method definition to load sensor data from a file
void TCPServer::loadSensorData()
{
	std::ifstream file(file_path); // Open the file
	std::string line;
	while (std::getline(file, line))
	{
		sensor_data.push_back(std::stoi(line)); // Read and store each sensor value
	}
}


// Method definition to accept an incoming client connection
int TCPServer::acceptClient()
{
	struct sockaddr_in address; // Structure to hold client address
	int addrlen = sizeof(address);
	int client_fd= accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen); // Accept client connection
	if (client_fd < 0)
	{
		perror("accept");
	}
	return client_fd; // Return client socket file descriptor
}


// Method definition to calculate sliding window average of the last ten sensor values
std::string TCPServer::calculateAverage()
{
	// If index value is end of sensor data, then return "Data Unavailable"
	if (current_index >= sensor_data.size())
	{
		return "Data unavailable";
	}
	
	int sum = 0; 
	int count = 0;
	for (size_t i = current_index; i < current_index + 10 && i < sensor_data.size(); ++i)
	{
		sum += sensor_data[i];
		++count;
	}
	current_index++; // Move the sliding window
	
	int average = sum / count; // Calcuate the average
	return std::to_string(average); // Return the average to client
}


// Method definition to handle client connection
void TCPServer::handleClient(int client_fd)
{
	std::string average = calculateAverage(); // Calculate the average sensor value
	send(client_fd, average.c_str(), average.size(), 0); // Send average to client
	close(client_fd); // Close client connection
}
