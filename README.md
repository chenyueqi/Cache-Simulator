# Cache-Simulator
 This repository serves as a lab in the course Computer Architecture, Department of Computer Science and Technology, Nanjing University

## Aim
 Implement a configurable cache simulator in C language

## Configuration Requirements(Input Parameters)
 Cache Size, Cacheline Size(block size), Associativity(direct-mapped/set-associative/fully-associative), Replacement Policy(LRU/Random)

## Simulated Cache Hierarchy
    L1 cache + Memory 					./src/LM
    L1 cache + L2 cache + Memory			./src/LLM
    L1 cache + Victim cache + L2 cache + Memory 	./src/LVLM

## Assumptions
    L1 cache access latency: 1 cycle
    Victim cache: 1 cycle
    L2 cache access latency: 10 cycles 
    Memory access latency: 100 cycles
    Memory address: 32 bits
    Cache miss will block the pipeline

## Result Requirements 
    Number of cache/memory accesses
    Number of cache/memory loads
    Number of cache/memory stores
    Average cache hit rate
    Cache hit rate for loads 
    Cache hit rate for stores
    CPU time(in cycle) and CPI

## Trace
    SPEC2000 CPU benchmarks
