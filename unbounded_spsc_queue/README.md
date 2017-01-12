# unbounded_spsc_queue.hpp
1024cores' [Unbounded SPSC Queue](1).

- Dequeue is always [wait-free](2).
- Enqueue is wait-free except that there is no cache node.

## Example

``` cpp
unbounded_spsc_queue<int> q;
auto t = std::thread([] {
  int v;
  while (q.dequeue(v)) ;
  std::cout << v << std::endl;
})
q.enqueue(10);
t.join();
```
## Usage

- `unbounded_spsc_queue<T>();`

  Create a unbounded SPSC queue.

- `void enqueue(const T &v);`  

  Enqueue an item using copy construction.
  
- `bool dequeue(T &v);`

  Dequeue first elment of queue. Return 'true' on success and 'false' if queue is empty.
  
[1]: http://www.1024cores.net/home/lock-free-algorithms/queues/unbounded-spsc-queue
[2]: https://en.wikipedia.org/wiki/Non-blocking_algorithm#Wait-freedom
