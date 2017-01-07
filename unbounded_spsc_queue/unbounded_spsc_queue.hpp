#include <cstddef>
#include <atomic>

template <typename T> T load_acquire(const T *addr) {
  T v = *const_cast<const T volatile *>(addr);
  std::atomic_signal_fence(std::memory_order_consume);
  return v;
}

template <typename T> void store_release(T *addr, T v) {
  std::atomic_signal_fence(std::memory_order_release);
  *const_cast<T volatile *>(addr) = v;
}

size_t const cache_line_size = 64;

template <typename T> class unbounded_spsc_queue {
public:
  unbounded_spsc_queue(void) {
    node *n = new node();
    head = first = tail_copy = tail = n;
  }

  ~unbounded_spsc_queue(void) {
    node *n = first;
    do {
      node *_n = n->next;
      delete n;
      n = _n;
    } while (n);
  }

  void enqueue(const T value) {
    node *n = new_node();
    n->value = value;
    store_release(&head->next, n);
    head = n;
  }

  bool dequeue(T &value) {
    if (load_acquire(&tail->next)) {
      value = tail->next->value;
      store_release(&tail, tail->next);
      return true;
    } else {
      return false;
    }
  }

private:
  struct node {
    node *next;
    T value;
  };

  node *new_node() {
    if (first != tail_copy) {
      node *n = first;
      first = first->next;
      return n;
    }

    tail_copy = load_acquire(&tail);
    if (first != tail_copy) {
      node *n = first;
      first = first->next;
      return n;
    }

    node *n = new node();
    return n;
  }

  // consumer
  node *tail;

  // padding forbid "False sharing"
  char padding[cache_line_size];

  // producer
  node *head;
  node *first;
  node *tail_copy;

  unbounded_spsc_queue(const unbounded_spsc_queue &);
  unbounded_spsc_queue &operator=(const unbounded_spsc_queue &);
};
