#include <unistd.h>
#include <stdio.h>
#include <thread>


#include "net.cpp"

int main(int argc, char **argv)
{

    // Getopt Vars
    int index;
    int c;
    // Arg Vars
    char *savefile = NULL;


    opterr = 0;

    while ((c = getopt(argc, argv, "s:")) != -1)
    {
        switch (c)
        {
            case 's':
                savefile = optarg;
                break;

        }
    }
    // Write read args
    printf("sarg = %s\n", savefile);
    // Write unread args
    for(index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    if(savefile == NULL) {
        abort();
    }

    // Initialize server socket
    int server_fd = create_socket(8080);

    // Lifetime Loop
    while (true) {
        int client_socket = accept_client(server_fd);
        // if client is valid
        if (client_socket >= 0) {
            std::thread client_thread(handle_client, client_socket);
            client_thread.detach(); // Lose Handler? Dispatches thread to keep running separately from the current thread.
        }

    }

    close(server_fd);
    return 0;
}