/**
 * @file queue.cpp
 * @author csg83
 *
 * @brief A simple queue abstraction for mission events
 */

#include "queue.hpp"

void Queue::enqueue(Event event) {
    if (!is_full()) {
        buffer[tail] = event;
        tail = (tail + 1) % BUFFER_SIZE;
        count++;
    }
}

uint8_t Queue::dequeue() {
    if (!is_empty()) {
        Event event = buffer[head];
        head = (head + 1) % BUFFER_SIZE;
        count--;
        return static_cast<uint8_t>(event);
    }
    return -1;
}

bool Queue::is_empty() {
    return count == 0;
}

bool Queue::is_full() {
    return count == BUFFER_SIZE;
}
