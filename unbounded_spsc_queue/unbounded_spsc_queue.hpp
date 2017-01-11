#include <cstddef>
#include <atomic>

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
        n->next.store(nullptr, std::memory_order_relaxed);
        head->next.store(n, std::memory_order_release);
        head = n;
    }

    bool dequeue(T &data) {
        node *n = tail.load(std::memory_order_relaxed);
        if (n = n->next.load(std::memory_order_consume)) {
            data = n->data;
            tail.store(n, std::memory_order_release);
            return true;
        } else {
            return false;
        }
    }

  private:
    struct node {
        std::atomic<node *> next;
        T data;
    };

    static constexpr size_t CACHELINE = 64;

    node *alloc_node(void) {
        if (first != tail_copy) {
            node *n = first;
            first = first->next;
            return n;
        }

        tail_copy = tail.load(std::memory_order_consume);
        if (first != tail_copy) {
            node *n = first;
            first = first->next;
            return n;
        }

        return new node();
    }

    alignas(CACHELINE) std::atomic<node *> tail;
    // Align to avoid false sharing between head and tail.
    alignas(CACHELINE) node *head;
    node *first;
    node *tail_copy;

    unbounded_spsc_queue(const unbounded_spsc_queue &);
    unbounded_spsc_queue &operator=(const unbounded_spsc_queue &);
};
