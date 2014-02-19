Public domain implementation of four different lock free queues:
  * SPSC lock free dynamic queue which requires a memory allocation with each insert.
  * MPSC lock free dynamic queue which requires a memory allocation with each insert.
  * SPSC wait free bound queue/ring buffer which which uses a fixed size pre-allocated buffer.
  * MPMC lock free bound queue/ring buffer which which uses a fixed size pre-allocated buffer.

## Performance
These number are on my Early 2013 Retina Macbook Pro (2.7 GHz i7). The latency variability of memory allocation can have a signifigant impact on the dynamic queues, sometimes halving throughput.

  Queue        | Throughput  
  :----------- | :-----------
  SPSC dynamic | 8 million   
  MPSC dynamic | 8 million   
  SPSC fixed   | 200 million 
  MPMC fixed   | 54 million  
