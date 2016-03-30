#ifndef __COM__
#define __COM__

#define cache_size 64000
#define cacheline_size 8
#define associative 2 	// 1: direct 2: set-associative 3: fully-associative
#define way_num 4 	// direct way_number = 1; fully-associative = cache_size/cacheline_size 
#define replacepolicy 1 // 1: LRU 2: Random , not used in direct-map

#define line_num cache_size/(cacheline_size * way_num)


unsigned int cycle_num;
unsigned int cache_access;
unsigned int mem_access;
unsigned int cache_load_num;
unsigned int mem_load_num;
unsigned int cache_store_num;
unsigned int mem_store_num;
unsigned int intr_num;

struct line_info
{
	unsigned char valid;
	unsigned int tag;
};

struct line_info cache[line_num][way_num];

void init_cache();
void construct_cache();
int run(char* trace_name);

#endif
