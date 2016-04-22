#ifndef __COM__
#define __COM__

#define cache_delay 1
#define cache2_delay 10
#define mem_delay 100


//cache 1 configuration
#define cache_size 32	//KB
#define cacheline_size 32 //bytes
#define associative 2 	// 1: direct 2: set-associative 3: fully-associative
#define way_num 4 	// direct way_number = 1; fully-associative = cache_size*1024/cacheline_size 
#define set_num cache_size*1024/(cacheline_size * way_num)

#define ADDR_offset_bit 5 // 2^ADDR_offset_bit = cacheline_size
#define ADDR_index_bit 8  // 2^ADDR_index_bit = set_num
#define ADDR_tag_bit 19   // 32 - ADDR_offset_bit - ADDR_set_bit

#define replacepolicy 1 // 1: LRU 2: Random


//cache 2 configuration 
#define cache2_size 2 	//MB
#define cacheline2_size 128 //bytes
#define associative2 2	//1.direct 2.set-associative 3.fully-associative
#define way2_num 8	//direct way_number = 1; fully-associative = cache2_size*1024*1024/cacheline2_size
#define set2_num cache2_size*1024*1024/(cacheline2_size * way2_num)

#define ADDR2_offset_bit 7 //2^ADDR2_offset_bit = cacheline2_size
#define ADDR2_index_bit 11 //2^ADDR2_index_bit = set2_num
#define ADDR2_tag_bit 14   //32 - ADDR2_offset_bit - ADDR2_tag_bit

#define replacepolicy2 1 //1.LRU 2.Random


unsigned long  cycle_num;
unsigned long instr_num;
unsigned long cycle_in_instr;

unsigned long cache_access;
unsigned long cache2_access;
unsigned long mem_access;

unsigned long cache_load_num;
unsigned long cache2_load_num;
unsigned long mem_load_num;

unsigned long cache_store_num;
unsigned long cache2_store_num;
unsigned long mem_store_num;

unsigned long cache_hit;
unsigned long cache2_hit;

unsigned long cache_load_hit;
unsigned long cache2_load_hit;

unsigned long cache_store_hit;
unsigned long cache2_store_hit;


struct line_info
{
	unsigned char valid;
	unsigned int fre; //only used in LRU
	unsigned int tag;
};

struct line_info cache[set_num][way_num];
struct line_info cache2[set2_num][way2_num];

void init_cache();

void construct_cache();

int run(char* trace_name);

#endif
