#include <cstddef>
#include <atomic>

template <typename T> T load_consume(const T *addr) {
    T v = *const_cast<const T volatile *>(addr);
    std::atomic_signal_fence(std::memory_order_consume);
    return v;
}

template <typename T> void store_release(T *addr, T v) {
    std::atomic_signal_fence(std::memory_order_release);
    *const_cast<T volatile *>(addr) = v;
}

template <typename T> class unbounded_spsc_queue {
  public:
    unbounded_spsc_queue(void) { head = first = tail = tail_copy = new node(); }

    ~unbounded_spsc_queue(void) {
        node *n = first;
        do {
            node *_n = n->next;
            delete n;
            n = _n;
        } while (n);
    }

    void enqueue(const T &data) {
        node *n = alloc_node();
        n->data = data;
        n->next = nullptr;
        store_release(&head->next, n);
        head = n;
    }

    bool dequeue(T &data) {
        // Be match to store_release(&head->next, n).
        if (load_consume(&tail->next)) {
            data = tail->next->data;
            store_release(&tail, tail->next);
            return true;
        } else {
            return false;
        }
    }

  private:
    struct node {
        node *next;
        T data;
    };

    static constexpr size_t CACHELINE = 64;

    node *alloc_node(void) {
        if (first != tail_copy) {
            node *n = first;
            first = first->next;
            return n;
        }

        // Be match to store_release(&tail, tail->next).
        tail_copy = load_consume(&tail);

        if (first != tail_copy) {
            node *n = first;
            first = first->next;
            return n;
        }

        return new node();
    }

    alignas(CACHELINE) node *tail;
    // Align to avoid false sharing between head and tail.
    alignas(CACHELINE) node *head;
    node *first;
    node *tail_copy;

    unbounded_spsc_queue(const unbounded_spsc_queue &);
    unbounded_spsc_queue &operator=(const unbounded_spsc_queue &);
};
