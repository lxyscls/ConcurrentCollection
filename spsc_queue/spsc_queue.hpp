#include <cstddef>

template <typename T, int capacity>
class spsc_queue {
	public:
		spsc_queue(const T &val) : head(0), tail(0), invalid_val(val) {
			for (int i = 0; i < capacity; i++) {
				buf[i] = invalid_val;
			}
		}
		spsc_queue(const spsc_queue &) = delete;
		spsc_queue &operator=(const spsc_queue &) = delete;

		bool enqueue(const T &data) {
			if (buf[tail] == invalid_val) {
				buf[tail] = data;
				tail += (tail+1 >= capacity) ? (1-capacity) : 1;
				return true;
			}
			return false;
		}

		bool dequeue(T &data) {
			if (buf[head] != invalid_val) {
				data = buf[head];
				buf[head] = invalid_val;
				head += (head+1 >= capacity) ? (1-capacity) : 1;
				return true;
			}
			return false;
		}

	private:
		static constexpr size_t CACHELINE = 64;

		T invalid_val;

		alignas(CACHELINE) unsigned int head;
		alignas(CACHELINE) unsigned int tail;

		char padding[CACHELINE - sizeof(tail)];

		T buf[capacity];
};
