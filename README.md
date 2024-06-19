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

- The `sensor_data.txt` file contains sufficient lines for initial tests.
- The server runs on a Linux environment.
- The server handles one client connection at a time for simplicity.

