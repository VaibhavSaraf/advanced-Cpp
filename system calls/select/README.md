# Select System Call Project

This project demonstrates how to use the `select` system call in C++ to manage multiple clients connecting to a single server. It's a simple example to understand how the server handles multiple client connections without requiring multiple threads or processes.

## How It Works (Simplified)

### Server (`server_select.cpp`)
- The server waits for connections from multiple clients using a single thread.
- It uses the `select` system call to monitor multiple sockets (server and client connections).
- When a client connects, the server:
  1. Accepts the connection.
  2. Reads the message sent by the client.
  3. Sends back a response (`Hello from server`).

### Client (`client_select.cpp`)
- The client connects to the server.
- Sends a message (`Hello from client`) to the server.
- Waits for the server's response and prints it.

### Main Program (`main_select.cpp`)
- The main program launches the server in one thread and multiple clients in separate threads.
- Each client connects to the server and interacts independently.

## Steps to Build and Run

1. **Build the Project**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Run the Server**:
   ```bash
   make run_server
   ```

3. **Run the Clients**:
   ```bash
   make run_clients
   ```

## Example Output

### Server:
```
New connection accepted
Received: Hello from client
Connection closed
```

### Client:
```
Message sent: Hello from client
Server: Hello from server
```

## Key Concepts
1. **Select System Call**:
   - `select` allows the server to monitor multiple sockets for activity (e.g., new connections, data to read).
   - It's a way to handle multiple clients without creating a new thread or process for each client.

2. **Single-Threaded Server**:
   - The server handles multiple connections using just one thread, making it efficient for simpler use cases.

3. **Client-Server Communication**:
   - The clients send messages to the server, which processes and responds to them.

## Why `select`?
- It's simple to use and widely supported.
- Ideal for scenarios with a small to moderate number of clients.
- However, for high-performance systems, consider using `epoll` or similar mechanisms.

## Limitations of `select`
1. **Scalability**:
   - Limited by the maximum number of file descriptors (usually 1024).

2. **Performance**:
   - The server must scan all file descriptors, which can be inefficient for a large number of clients.
