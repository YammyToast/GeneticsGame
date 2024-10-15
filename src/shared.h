#ifndef _SHARED_CPP_

#include <mutex>
#include <vector>

#include "message_queue.cpp"

std::mutex shared_lock;

struct
{   
    std::vector<int> client_fds;
    MessageQueue<std::string> message_queue;
} shared_struct;

#endif