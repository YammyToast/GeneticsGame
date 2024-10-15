#ifndef _NET_CPP_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#include "net.h"
#include "shared.h"

int create_socket(int __port)
{
    int server_fd;
    struct sockaddr_in address;

    // Create the Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("Socket failed to open");
        exit(EXIT_FAILURE);
    }

    // Create Address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // endian form checking
    address.sin_port = htons(__port);

    // bind socket and check for error
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Could not bind socket");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("Error listening on server file descriptor");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", __port);
    return server_fd;
}

int accept_client(int __server_fd)
{
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    int client_socket = accept(__server_fd, (struct sockaddr *)&client_address, &client_len);

    if (client_socket < 0)
    {
        perror("Error accepting client\n");
        return -1;
    }
    printf("New client connected: %d\n", client_socket);
    return client_socket;
}

void handle_client(int __client_socket)
{
    char buffer[1024] = {0};
    while (true)
    {
        int valread = read(__client_socket, buffer, sizeof(buffer));
        // if nothing is read dc the client
        if (valread <= 0)
        {
            printf("Client disconnected.\n");
            close(__client_socket);
            break;
        }
        printf("Recieved: %s\n", buffer);

        send(__client_socket, buffer, valread, 0);
        memset(buffer, 0, sizeof(buffer));


    }
}

#endif