#!/bin/bash


# Defining the number of requests, server address and port
NUM_REQUESTS=100
SERVER_ADDRESS="localhost"
SERVER_PORT=12345


# Function defenition for making the request to server
make_request()
{
	echo "Requesting sensor value from server..."
	nc $SERVER_ADDRESS $SERVER_PORT
	echo "Request Complete."
}


# Loop to create multiple requests
for ((i=0; i<NUM_REQUESTS; i++))
do
	make_request &
	# sleep 1
done


# Waiting for all jobs to be done
wait

echo "All requests completed."
