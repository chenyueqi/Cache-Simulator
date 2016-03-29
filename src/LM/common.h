#ifndef __COM__
#define __COM__

#define cache_size 64000
#define cacheline_size 8
#define associative 1 	// 1: direct 2: set-associative 3: fully-associative
#define way_number 4 	// only used in set-associativity, please set 1 in other situation
#define replacepolicy 1 // 1: LRU 2: Random , not used in direct-map

#define line_num cache_size/cacheline_size


unsigned int cycle_num;
/*TODO define of statistic information*/

struct line_info
{
	unsigned char valid;
	unsigned int tag;
};

struct line_info cache[line_num];

void init_cache();
void construct_cache();
void run(char* trace_name);

#endif
