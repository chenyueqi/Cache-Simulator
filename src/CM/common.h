#ifndef __COM__
#define __COM__

#define cache_delay 1
#define mem_delay 100

#define cache_size 64
#define cacheline_size 8
#define associative 2 	// 1: direct 2: set-associative 3: fully-associative
#define way_num 4 	// direct way_number = 1; fully-associative = cache_size/cacheline_size 
#define set_num cache_size*1024/(cacheline_size * way_num)

#define ADDR_offset_bit 5
#define ADDR_set_bit 11 
#define ADDR_tag_bit 16

#define replacepolicy 1 // 1: LRU 2: Random , not used in direct-map



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
