#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>

class TCPServer {
	public:
		TCPServer(int port, const std::string& file_path);
		void run();
	private:
		int server_fd;
		int port;
		std::string file_path;
		std::vector<int> sensor_data;
		size_t current_index;
		
		void loadSensorData();
		int acceptClient();
		std::string calculateAverage();
		void handleClient(int client_fd);
};

#endif // SERVER_H
