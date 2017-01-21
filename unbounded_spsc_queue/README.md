# unbounded_spsc_queue.hpp
1024cores' [Unbounded SPSC Queue](1).

- Dequeue is always [wait-free](2).
- Enqueue is wait-free except that there is no cache node.

## Example

``` cpp
unbounded_spsc_queue<int> q;
auto t = std::thread([] {
  int v;
  while (!q.dequeue(v)) ;
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
  
## Benchmarks

Be the same as [rigtorp's SPSCQueue][3]'s.

The following numbers are for a 2 socket machine with 2 x Intel(R) Xeon(R) CPU E5-2658 v3 @ 2.20GHz.

| NUMA Node / Core / Hyper-Thread | Throughput (ops/ms) | Latency RTT (ns) |
| ------------------------------- | -------------------:| ----------------:|
| #0,#0,#0 & #0,#0,#1             |              242332 |               58 |
| #0,#0,#0 & #0,#1,#0             |              137727 |              387 |
| #0,#0,#0 & #1,#0,#0             |               22787 |              836 |

[rigtorp's][3]

| NUMA Node / Core / Hyper-Thread | Throughput (ops/ms) | Latency RTT (ns) |
| ------------------------------- | -------------------:| ----------------:|
| #0,#0,#0 & #0,#0,#1             |               41223 |              112 |
| #0,#0,#0 & #0,#1,#0             |               20061 |              315 |
| #0,#0,#0 & #1,#0,#0             |               15842 |              722 |
  
[1]: http://www.1024cores.net/home/lock-free-algorithms/queues/unbounded-spsc-queue
[2]: https://en.wikipedia.org/wiki/Non-blocking_algorithm#Wait-freedom
[3]: https://github.com/rigtorp/SPSCQueue
