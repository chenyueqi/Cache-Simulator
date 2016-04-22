# Cache-Simulator
 This repository serves as a lab in the course Computer Architecture, Department of Computer Science and Technology, Nanjing University

## Aim
 Implement a configurable cache simulator in C language

## Configuration Requirements(Input Parameters)
 Cache Size, Cacheline Size(block size), Associativity(direct-mapped/set-associative/fully-associative), Replacement Policy(LRU/Random)

## Simulated Cache Hierarchy
    L1 cache + Memory 					./src/CM
    L1 cache + L2 cache + Memory			./src/CCM
    L1 cache + Victim cache + L2 cache + Memory 	./src/CVCM

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

    Different Cache Hierarchy's result in ./result/CM ./result/CCM ./result/CVCM respectively

## Trace
    SPEC2000 CPU benchmarks  ./test/

## file structure
    take CM(L1 cache + Memory) for example

    ./README.md .................. file you are opening
    ./report ..................... directory for report
    ./result ..................... directory for result
    	./result/CM .............. directory for L1 cache + Memory result
	./result/CCM ............. directory for L1 cache + L2 cache + Memory result
	./result/CVCM ............ directory for L1 cache + Victim cache + L2 cache + Memory result
    ./src ........................ directory for source code
    	./src/CM ................. directory for L1 cache + Memory source code
	    ./src/CM/Makefile .... Makefile
	    ./src/CM/main.c ...... main function
	    ./src/CM/common.h .... common declarations 
	    ./src/CM/cache.h ..... cache implementation	
	./src/CCM ................ directory for L1 cache + L2 cache + Memory source code
	    ...
	./src/CVCM ............... directory for L1 cache + Victim cache + L2 cache + Memory source code
	    ...
     ./test ...................... directory for SPEC2000 CPU benchmarks 


