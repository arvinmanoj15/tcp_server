#ifndef SERVER_H
#define SERVER_H

#include <vector> // Including the vectore header file
#include <string> // Including the string header file


// Declaration of the TCPServer class
class TCPServer {
	public:
		// Constructor for TCPServer
		TCPServer(int port, const std::string& file_path);
		// Method to run the TCP server
		void run();
	private:
		int server_fd; // File description for the server socket
		int port; // Port number for the server to listen
		std::string file_path; // Path of the sensor data file
		std::vector<int> sensor_data; // Vector to store sensor data
		size_t current_index; // Current index for reading sensor data 
		
		// Method to load sensor data from file
		void loadSensorData();
		
		// Method to accept incoming client connection and returns file descriptor 
		int acceptClient();
		
		// Method to calcuate sliding window average of last 10 sensor values and returns average as string
		std::string calculateAverage();
		
		// Method to handle client connection, parameter taken : Client socket file descriptor
		void handleClient(int client_fd);
};

#endif // SERVER_H
