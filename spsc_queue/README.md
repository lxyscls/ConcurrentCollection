# spsc_queue.hpp
An improved implementation of [Lamport's circular buffer][1].

- Dequeue and Enqueue are both [wait-free](2).

## Example

``` cpp
spsc_queue<int, 256> q(-1);
auto t = std::thread([] {
  int v;
  while (!q.dequeue(v)) ;
  std::cout << v << std::endl;
})
while(!q.enqueue(10));
t.join();
```
## Usage

- `spsc_queue<T, capacity>(T invalid_val);`

  Create a bounded SPSC queue, give the buffer size and an **never used value**.

- `bool enqueue(const T &v);`  

  Enqueue an item using copy construction. Return 'true' on success and 'false' if queue is full.
  
- `bool dequeue(T &v);`

  Dequeue first elment of queue. Return 'true' on success and 'false' if queue is empty.
  
## Attention

The **T** must be some primitive types or pointer.
  
## Benchmarks

Be the same as [rigtorp's SPSCQueue][3]'s.

The following numbers are for a 2 socket machine with 2 x Intel(R) Xeon(R) CPU E5-2658 v3 @ 2.20GHz.

| NUMA Node / Core / Hyper-Thread | Throughput (ops/ms) | Latency RTT (ns) |
| ------------------------------- | -------------------:| ----------------:|
| #0,#0,#0 & #0,#0,#1             |              192445 |               63 |
| #0,#0,#0 & #0,#1,#0             |              190213 |              279 |
| #0,#0,#0 & #1,#0,#0             |               94403 |              752 |

[rigtorp's][3]

| NUMA Node / Core / Hyper-Thread | Throughput (ops/ms) | Latency RTT (ns) |
| ------------------------------- | -------------------:| ----------------:|
| #0,#0,#0 & #0,#0,#1             |               41223 |              112 |
| #0,#0,#0 & #0,#1,#0             |               20061 |              315 |
| #0,#0,#0 & #1,#0,#0             |               15842 |              722 |
  
[1]: http://research.microsoft.com/en-us/um/people/lamport/pubs/proving.pdf
[2]: https://en.wikipedia.org/wiki/Non-blocking_algorithm#Wait-freedom
[3]: https://github.com/rigtorp/SPSCQueue
