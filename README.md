# TCP Server

## Instructions to Compile and Run

1. **Clone the repository and navigate into the project directory:**
    ```bash
    git clone <repository-url>
    cd tcp_server
    ```

2. **Place the sensor data file in the project directory and name it `sensor_data.txt`.**

3. **Compile the project using CMake and make:**
    ```bash
    cmake .
    make
    ```

4. **Run the server:**
    ```bash
    ./tcp_server
    ```

5. **Test the server using netcat in another terminal:**
    ```bash
    nc localhost 12345
    ```

6. **Test the server by requesting multiple connections using the provided script:**
    ```bash
    ./test_server.sh
    ```

## Description

The TCP server listens for client connections on port 12345. When a client connects, the server sends the next available sensor value, which is the average of the last ten values read from the `sensor_data.txt` file. If fewer than ten values have been read, the average is calculated using the available values. When the server reaches the end of the file, it sends "Data unavailable" to any connecting clients.

## Assumptions

1. **Sensor Data File:**
   - The `sensor_data.txt` file is located in the project directory.
   - Each line in the `sensor_data.txt` file contains a single numeric sensor value.

2. **Environment:**
   - The server is designed to run in a Linux environment.
   - The necessary build tools (`cmake`, `make`, `g++`) are installed on the system.

3. **Client Connections:**
   - The server handles one client connection at a time.
   - The server can handle multiple client connections sequentially, but not concurrently.

4. **Error Handling:**
   - The server includes basic error handling for socket operations and file I/O.
   - In case of errors (e.g., file not found, socket binding issues), appropriate error messages will be displayed, and the server will exit gracefully.

5. **Resource Management:**
   - The server ensures that client connections are properly closed after handling each request.
   - Sensor data is loaded into memory at the start of the server and remains in memory for the duration of the server's execution.

6. **Testing:**
   - The provided `test_server.sh` script is used to test the server with multiple connections.
   - The script creates multiple client requests without any delay between them to simulate a more intense load on the server.

By following these assumptions, you can ensure that the TCP server operates as expected and handles client connections appropriately.
