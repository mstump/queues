#include <iostream>
#include <thread>

#include "spsc-queue.hpp"

#define COUNT 100000000

typedef spsc_queue_t<int> queue_t;

void
consumer_func(
    queue_t* queue)
{
    int count = COUNT;
    int value = 0;

    while (count > 0) {
        if (queue->dequeue(value)) {
            --count;
        }
    }
}

void
producer_func(
    queue_t* queue)
{
    for (int count = 0; count < COUNT; ++count) {
        queue->enqueue(count);
    }
}


int
main()
{
    queue_t queue;

    typedef std::chrono::high_resolution_clock clock_t;
    typedef std::chrono::time_point<clock_t> time_t;
    time_t start;
    time_t end;

    start = clock_t::now();
    std::thread producer(std::bind(&producer_func, &queue));
    std::thread consumer(std::bind(&consumer_func, &queue));

    producer.join();
    consumer.join();
    end = clock_t::now();

    std::cout << (end - start).count() * ((double) std::chrono::high_resolution_clock::period::num / std::chrono::high_resolution_clock::period::den) << " seconds" << std::endl;
    return 0;
}
