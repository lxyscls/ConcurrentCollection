#include <cstddef>
#include <atomic>

template <typename T, int capacity> class spsc_queue {
  public:
    spsc_queue(const T &val) : head(0), tail(0), invalid_val(val) {
        for (int i = 0; i < capacity; i++) {
            buf[i] = invalid_val;
        }
    }
    spsc_queue(const spsc_queue &) = delete;
    spsc_queue &operator=(const spsc_queue &) = delete;

    bool enqueue(const T &data) {
        if (buf[tail].load(std::memory_order_acquire) == invalid_val) {
            buf[tail].store(data, std::memory_order_release);
            tail = (tail + 1) % capacity;
            return true;
        }
        return false;
    }

    bool dequeue(T &data) {
        if (buf[head].load(std::memory_order_acquire) != invalid_val) {
            data = buf[head].load(std::memory_order_relaxed);
            buf[head].store(invalid_val, std::memory_order_release);
            head = (head + 1) % capacity;
            return true;
        }
        return false;
    }

  private:
    static constexpr size_t CACHELINE = 64;

    alignas(CACHELINE) unsigned int head;
    alignas(CACHELINE) unsigned int tail;

    char padding[CACHELINE - sizeof(tail)];

    std::atomic<T> buf[capacity];
    T invalid_val;
};
