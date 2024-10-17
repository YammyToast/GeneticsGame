#include <unistd.h>
#include <stdio.h>
#include <thread>
#include <cstdio>

#include "spdlog/spdlog.h"

#include "net.cpp"

void worker_thread()
{
    while (true)
    {
        std::string message = shared_struct.message_queue.pop();
        printf("Processing Message: %s\n", message.data());

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char **argv)
{
    
    spdlog::info("Welcome to SpdLog!");

    // Getopt Vars
    int index;
    int c;
    // Arg Vars
    char *savefile = NULL;
    int num_worker_threads = 1;

    opterr = 0;

    while ((c = getopt(argc, argv, "s:c:")) != -1)
    {
        switch (c)
        {
        case 's':
            savefile = optarg;
            break;
        case 'c':
            num_worker_threads = std::stoi(optarg);
            break;
        }
    }
    // Write read args
    // write_log(sprintf("SaveArg = %s, WorkerThreads(carg) = %s", savefile, num_worker_threads));
    // printf("sarg = %s carg = %d\n", savefile, num_worker_threads);

    // Write unread args
    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    if (savefile == NULL)
    {
        abort();
    }

    // Initialize worker thread(s)
    std::vector<std::thread> workers;
    for (int i = 0; i < num_worker_threads; i++)
    {
        workers.emplace_back(worker_thread);
    }

    // Initialize server socket
    int server_fd = create_socket(8080);

    // Lifetime Loop
    while (true)
    {
        int client_socket = accept_client(server_fd);
        // if client is valid
        if (client_socket >= 0)
        {
            std::thread client_thread(handle_client, client_socket);
            client_thread.detach(); // Lose Handler? Dispatches thread to keep running separately from the current thread.
        }
    }

    close(server_fd);
    return 0;
}