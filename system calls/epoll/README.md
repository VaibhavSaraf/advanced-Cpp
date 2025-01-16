Project Overview
This project demonstrates how to handle multiple clients connecting to a single server using two popular techniques in Linux: epoll (an efficient I/O event notification system) and select (a less efficient, older mechanism). However, the code provided exclusively uses epoll for high performance. Below is a detailed breakdown of the three main files (server.cpp, client.cpp, and main.cpp).

File 1: client.cpp
Purpose
This file implements a simple client that:

Creates a socket and connects to the server on 127.0.0.1:8080.
Sends a message to the server.
Waits for and prints the server's response.
Key Components
Socket Creation:

int sock = socket(AF_INET, SOCK_STREAM, 0);
A TCP socket is created using the socket() function.
Server Address Setup:

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
Configures the server address as 127.0.0.1 (localhost) and port 8080.
Connection and Communication:

The client connects to the server using connect().
Sends a message (Hello from client) to the server.
Reads the server's response using read().
Message Interaction:

Logs the sent message and the server’s response to the console.
File 2: server.cpp
Purpose
The server can handle multiple clients simultaneously using the epoll API, which efficiently manages multiple file descriptors.

Key Components
Socket Initialization:

server_fd = socket(AF_INET, SOCK_STREAM, 0);
setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
bind(server_fd, (struct sockaddr\*)&address, sizeof(address));
listen(server_fd, 3);
Creates a listening socket for incoming connections.
Sets socket options to allow reusing the address and port.
Binds the socket to 0.0.0.0:8080 (accepts connections from any interface).
Epoll Setup:

epoll_fd = epoll_create1(0);
ev.events = EPOLLIN;
ev.data.fd = server_fd;
epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev);
Creates an epoll instance.
Monitors the server_fd for incoming connections.
Event Handling Loop:

while (true) {
int n_fds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
for (int i = 0; i < n_fds; i++) {
if (events[i].data.fd == server_fd) {
// Accept new connections
} else {
// Handle data from clients
}
}
}
Uses epoll_wait() to block until one or more events occur.
Distinguishes between new connections and incoming data.
Communication with Clients:

When a client sends data, the server reads it, logs it, and responds with Hello from server.
Edge Triggered Mode (EPOLLET):

Ensures efficient handling by processing all available data in a single event notification.
File 3: main.cpp
Purpose
This file serves as a driver program to:

Start the server in a separate thread.
Create and launch multiple client threads that connect to the server.
Key Components
Server Thread:

std::thread serverThread(runServer);
Launches the server process using system("./server") in a separate thread.
Multiple Clients:

for (int i = 0; i < clientCount; ++i) {
clientThreads.emplace_back([]() { system("./client"); });
}

Spawns a specified number (clientCount) of client threads, each running ./client.
Thread Synchronization:

Ensures all threads (server and clients) complete using join().
Project Workflow
Server Initialization:

The server listens for incoming connections on 127.0.0.1:8080 and uses epoll to manage multiple simultaneous client sockets.
Client-Server Communication:

Each client connects to the server, sends a message (Hello from client), and waits for the server's response.
Server Response:

The server receives messages from clients, processes them, and responds with Hello from server.
Handling Multiple Clients:

The epoll mechanism allows the server to handle multiple clients concurrently without blocking, ensuring high performance.
Advantages of epoll over select
Scalability:

epoll can handle thousands of connections efficiently, while select is limited by the maximum file descriptor count.
Event-Driven:

epoll only notifies the server when an event occurs, reducing unnecessary checks.
Efficient Memory Usage:

Unlike select, which requires recreating the list of monitored file descriptors, epoll maintains a kernel-managed list.

#Compilation and Execution
Steps to Build and Run:
Build the project:

mkdir build
cd build
cmake ..
make

Run the server:

make run_server
Run the clients through the main program:

make run_clients

Project Outputs
Server Console:

New connection accepted
Received: Hello from client
Connection closed

Client Console:

Message sent: Hello from client
Server: Hello from server
This project demonstrates the power of epoll for concurrent socket programming, suitable for building scalable and efficient network servers.
