#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <fcntl.h>

#define PORT 8080
#define MAX_EVENTS 10

int main()
{
    int server_fd, new_socket, epoll_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    struct epoll_event ev, events[MAX_EVENTS];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

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

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1)
    {
        perror("epoll_ctl: server_fd");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        int n_fds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < n_fds; i++)
        {
            if (events[i].data.fd == server_fd)
            {
                new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                if (new_socket < 0)
                {
                    perror("accept");
                    continue;
                }
                fcntl(new_socket, F_SETFL, O_NONBLOCK);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = new_socket;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &ev);
                std::cout << "New connection accepted" << std::endl;
            }
            else
            {
                char buffer[1024] = {0};
                int valread = read(events[i].data.fd, buffer, 1024);
                if (valread == 0)
                {
                    close(events[i].data.fd);
                    std::cout << "Connection closed" << std::endl;
                }
                else
                {
                    std::cout << "Received: " << buffer << std::endl;
                    std::string response = "Hello from server";
                    send(events[i].data.fd, response.c_str(), response.size(), 0);
                }
            }
        }
    }

    close(server_fd);
    return 0;
}