spsc-lockfree-queue
===================

A public domain implementation of two different single producer,
single consumer lock free queues:
  * Dynamic queue which requires a memory allocation with each insert.
  * Fixed size, wait free, bound queue (ring buffer) which allocates no memory.

## Performance
On my Early 2013 Retina Macbook Pro (2.7 GHz i7) I'm able to obtain
151.188 million enqueue/dequeue pairs per second with the bound queue,
and 8.466 million with the dynamic queue. The latency variability of memory
allocation can have a signifigant impact on the dynamic queue,
sometimes halving throughput.