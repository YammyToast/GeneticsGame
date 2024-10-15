#ifndef _NET_CPP_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int create_socket(int __port)
{
    int server_fd;
    struct sockaddr_in address;

    // Create the Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket Failed to Open");
        exit(EXIT_FAILURE);
    }

    // Create Address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // endian form checking
    address.sin_port = htons(__port);

    // bind socket and check for error
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
}

int accept_client(int __server_fd)
{
}

void handle_client(int __client_socket)
{
}

#endif