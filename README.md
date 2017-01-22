# Collection of concurrent data structures
### Harware platform
- X86-32/64

### Queue

#### SPSC Queue
>In the end of 1970's, [Leslie Lamport][1] proved that, under Sequential Consistency memory model, a Single-Producer/Single-Consumer circular buffer can be implemented without using explicit synchronization mechanisms between the producer and the consumer. (From Massimo Torquati's [\<Single-Producer/Single-Consumer Queues on Shared Cache Multi-Core Systems\>][2])

I have found two implementations of Lamport's SPSC Queue from the Internet. One is [KjellKod.cc's][3], other is [rigtorp's][4].

- Unbounded SPSC Queue
- Bounded SPSC Queue

[1]: https://en.wikipedia.org/wiki/Leslie_Lamport
[2]: https://arxiv.org/pdf/1012.1824.pdf
[3]: https://www.codeproject.com/articles/43510/lock-free-single-producer-single-consumer-circular
[4]: https://github.com/rigtorp/SPSCQueue
