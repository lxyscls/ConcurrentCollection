#include "unbounded_spsc_queue.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <cassert>

int main(void) {
    const size_t iter = 100000;
    unbounded_spsc_queue<size_t> q;
    std::atomic<bool> flag(false);
    std::thread producer([&] {
        while (!flag)
            ;
        for (size_t i = 0; i < iter; ++i) {
            q.enqueue(i);
        }
    });

    size_t sum = 0;
    auto start = std::chrono::system_clock::now();
    flag = true;
    for (size_t v, i = 0; i < iter; ++i) {
        if (q.dequeue(v))
            sum += v;
        else
            --i;
    }
    auto end = std::chrono::system_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    assert(sum == iter * (iter - 1) / 2);

    producer.join();

    std::cout << duration.count() / iter << " ns/iter" << std::endl;

    return 0;
}
