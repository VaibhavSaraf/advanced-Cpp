# Project Overview

This project demonstrates how to handle multiple clients connecting to a single server using two popular techniques in Linux: epoll (an efficient I/O event notification system) and select (a less efficient, older mechanism). However, the code provided exclusively uses `select` for understanding its functionality. Below is a detailed breakdown of the three main files (`server_select.cpp`, `client_select.cpp`, and `main_select.cpp`).

## File 1: `client_select.cpp`

### Purpose

This file implements a simple client that:

- Creates a socket and connects to the server on `127.0.0.1:8080`.
- Sends a message to the server.
- Waits for and prints the server's response.

### Key Components

**Socket Creation:**

```cpp
int sock = socket(AF_INET, SOCK_STREAM, 0);
```

A TCP socket is created using the `socket()` function.

**Server Address Setup:**

```cpp
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
```

Configures the server address as `127.0.0.1` (localhost) and port `8080`.

**Connection and Communication:**

- The client connects to the server using `connect()`.
- Sends a message (`Hello from client`) to the server.
- Reads the server's response using `read()`.

**Message Interaction:**
Logs the sent message and the server’s response to the console.

## File 2: `server_select.cpp`

### Purpose

The server can handle multiple clients simultaneously using the `select` system call, which monitors multiple file descriptors.

### Key Components

**Socket Initialization:**

```cpp
server_fd = socket(AF_INET, SOCK_STREAM, 0);
setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
bind(server_fd, (struct sockaddr*)&address, sizeof(address));
listen(server_fd, 3);
```

- Creates a listening socket for incoming connections.
- Sets socket options to allow reusing the address and port.
- Binds the socket to `0.0.0.0:8080` (accepts connections from any interface).

**Select Setup:**

- Initializes the `fd_set` structure to monitor multiple file descriptors.
- Adds the server's file descriptor (`server_fd`) to the set.

**Event Handling Loop:**

```cpp
while (true) {
    FD_ZERO(&readfds);
    FD_SET(server_fd, &readfds);
    max_sd = server_fd;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        // Add active client sockets to readfds
    }

    activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
    if (FD_ISSET(server_fd, &readfds)) {
        // Accept new connections
    }
}
```

Uses `select()` to block until one or more events occur.
Distinguishes between new connections and incoming data.

**Communication with Clients:**

- When a client sends data, the server reads it, logs it, and responds with `Hello from server`.

## File 3: `main_select.cpp`

### Purpose

This file serves as a driver program to:

- Start the server in a separate thread.
- Create and launch multiple client threads that connect to the server.

### Key Components

**Server Thread:**

```cpp
std::thread serverThread(runServer);
```

Launches the server process using `./server_select` in a separate thread.

**Multiple Clients:**

```cpp
for (int i = 0; i < clientCount; ++i) {
    clientThreads.emplace_back([] {
        system("./client_select");
    });
}
```

Spawns a specified number (`clientCount`) of client threads, each running `./client_select`.

**Thread Synchronization:**
Ensures all threads (server and clients) complete using `join()`.

## Project Workflow

1. **Server Initialization:**
   The server listens for incoming connections on `127.0.0.1:8080` and uses `select` to manage multiple simultaneous client sockets.

2. **Client-Server Communication:**
   Each client connects to the server, sends a message (`Hello from client`), and waits for the server's response.

3. **Server Response:**
   The server receives messages from clients, processes them, and responds with `Hello from server`.

4. **Handling Multiple Clients:**
   The `select` mechanism allows the server to handle multiple clients concurrently without blocking, ensuring good performance.

## Advantages of `select`

1. **Widely Supported:**

   - `select` is available on almost all UNIX-like operating systems.

2. **Simple API:**
   - Easy to understand and use for smaller projects.

## Limitations of `select`

1. **Scalability:**

   - Limited by the maximum number of file descriptors (usually 1024).

2. **Performance:**
   - The server must scan all file descriptors, which can be inefficient for a large number of clients.

## Steps to Build and Run

1. **Build the project:**

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Run the server:**

   ```bash
   make run_server
   ```

3. **Run the clients through the main program:**
   ```bash
   make run_clients
   ```

## Project Outputs

### Server Console:

```
New connection accepted
Received: Hello from client
Connection closed
```

### Client Console:

```
Message sent: Hello from client
Server: Hello from server
```
