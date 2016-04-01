#ifndef __COM__
#define __COM__

#define cache_delay 1
#define mem_delay 100

#define cache_size 32
#define cacheline_size 32
#define associative 2 	// 1: direct 2: set-associative 3: fully-associative
#define way_num 4 	// direct way_number = 1; fully-associative = cache_size*1024/cacheline_size 
#define set_num cache_size*1024/(cacheline_size * way_num)

#define ADDR_offset_bit 5 // 2^ADDR_offset_bit = cacheline_size
#define ADDR_index_bit 8  // 2^ADDR_index_bit = set_num
#define ADDR_tag_bit 19   // 32 - ADDR_offset_bit - ADDR_set_bit

#define replacepolicy 1 // 1: LRU 2: Random



unsigned long  cycle_num;
unsigned long cache_access;
unsigned long mem_access;
unsigned long cache_load_num;
unsigned long mem_load_num;
unsigned long cache_store_num;
unsigned long mem_store_num;
unsigned long instr_num;
unsigned long cycle_in_instr;

struct line_info
{
	unsigned char valid;
	unsigned int fre; //only used in LRU
	unsigned int tag;
};

struct line_info cache[set_num][way_num];

void init_cache();
void construct_cache();
int run(char* trace_name);

#endif
