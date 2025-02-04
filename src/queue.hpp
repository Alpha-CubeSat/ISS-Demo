

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "constants.hpp"
#include <stdint.h>

#define BUFFER_SIZE 10

class Queue {
public:
    void enqueue(Event event);
    uint8_t dequeue();
    bool is_empty();
    bool is_full();

private:
    Event buffer[BUFFER_SIZE];
    int head = 0, tail = 0, count = 0;
};

#endif  // QUEUE_HPP
