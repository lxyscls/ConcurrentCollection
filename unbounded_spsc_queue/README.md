# unbounded_spsc_queue.hpp
1024cores' [Unbounded SPSC Queue](1).

- Dequeue is always [wait-free](2).
- Enqueue is wait-free except that there is no cache node.

[1]: http://www.1024cores.net/home/lock-free-algorithms/queues/unbounded-spsc-queue
[2]: https://en.wikipedia.org/wiki/Non-blocking_algorithm#Wait-freedom
