# Collection of concurrent data structures
### Harware platform
- X86-32/64

### Queue

#### SPSC Queue
>In the end of 1970's, [Leslie Lamport][1] proved that, under Sequential Consistency memory model, a Single-Producer/Single-Consumer circular buffer can be implemented without using explicit synchronization mechanisms between the producer and the consumer. (From Massimo Torquati's [\<Single-Producer/Single-Consumer Queues on Shared Cache Multi-Core Systems\>][2])

I have found two implementations of [Lamport's SPSC Queue][5] which is based on circular buffer from the Internet. One is [KjellKod.cc's][3], another is [rigtorp's][4]. And as below there are two other implementations, one is based on linked-list, another has made some improvements on [Lamport's][5]. 

- Unbounded SPSC Queue
  
- Bounded SPSC Queue
  
##### Benchmark

Be the same as [rigtorp's][4].

The following numbers are for a 2 socket machine with 2 x Intel(R) Xeon(R) CPU E5-2658 v3 @ 2.20GHz.

Unbounded SPSC Queue

| NUMA Node / Core / Hyper-Thread | Throughput (ops/ms) | Latency RTT (ns) |
| ------------------------------- | -------------------:| ----------------:|
| #0,#0,#0 & #0,#0,#1             |              242332 |               58 |
| #0,#0,#0 & #0,#1,#0             |              137727 |              387 |
| #0,#0,#0 & #1,#0,#0             |               22787 |              836 |

SPSC Queue

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

[1]: https://en.wikipedia.org/wiki/Leslie_Lamport
[2]: https://arxiv.org/pdf/1012.1824.pdf
[3]: https://www.codeproject.com/articles/43510/lock-free-single-producer-single-consumer-circular
[4]: https://github.com/rigtorp/SPSCQueue
[5]: http://research.microsoft.com/en-us/um/people/lamport/pubs/proving.pdf
[6]: http://www.1024cores.net/home/lock-free-algorithms/queues/unbounded-spsc-queue
