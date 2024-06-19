#include "server.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>


TCPServer::TCPServer(int port, const std::string& file_path) 
	: port(port), file_path(file_path), current_index(0) {}


void TCPServer::run()
{
	loadSensorData();
	
	struct sockaddr_in address;
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
	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	
	while (true)
	{
		int client_fd = acceptClient();
		if (client_fd >= 0)
		{
			handleClient(client_fd);
		}
	}
}


void TCPServer::loadSensorData()
{
	std::ifstream file(file_path);
	std::string line;
	while (std::getline(file, line))
	{
		sensor_data.push_back(std::stoi(line));
	}
}

int TCPServer::acceptClient()
{
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int client_fd= accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (client_fd < 0)
	{
		perror("accept");
	}
	return client_fd;
}


std::string TCPServer::calculateAverage()
{
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
	current_index++;
	
	int average = sum / count;
	return std::to_string(average);
}


void TCPServer::handleClient(int client_fd)
{
	std::string average = calculateAverage();
	send(client_fd, average.c_str(), average.size(), 0);
	close(client_fd);
}
