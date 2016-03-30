#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"common.h"

void access_cache(char instr, unsigned int addr);
void access_mem(char instr);

void init_cache()
{
    int i = 0;
    int j = 0;
    for(; i < set_num ; i++)
	for(; j < way_num ; j++)
	{
	    cache[i][j].valid = 0;
	    cache[i][j].tag = 0;
	    cache[i][j].fre = 0;
	}

    cycle_num = 0;
    cache_access = 0;
    mem_access = 0;
    cache_load_num = 0;
    mem_load_num = 0;
    cache_store_num = 0;
    mem_store_num = 0;
    instr_num = 0;

    return ;
}

void construct_cache()
{
    init_cache();
}

int run(char* trace_name)
{
    FILE* trace = fopen(trace_name , "r");
    if(!trace)
    {
	fprintf(stderr , "Failed: trace file could not be open %s %d\n" , __FILE__ , __LINE__);
	return 1;
    }

    while(!feof(trace))
    {
	char buffer[20];
	fgets(buffer , 20 , trace);

	char* p = NULL;

	p  = strtok(buffer , " ");
	char instr = p[0];

	char *pEnd;
	p = strtok(NULL, " ");

	if(p == NULL)
	    break;
	unsigned int addr = (unsigned int)strtol(p, &pEnd , 16);

	p = strtok(NULL , " \n");
	unsigned int delay = (unsigned int)strtol(p, &pEnd , 10);
	
	access_cache(instr, addr);

	instr_num++;
	cycle_num += delay;
    }

    fclose(trace);
    return 0;
}

void access_cache(char instr, unsigned int addr)
{
    cache_access++;

    unsigned int offset = (addr << (ADDR_set_bit + ADDR_tag_bit)) >> (ADDR_set_bit + ADDR_tag_bit);
    unsigned int index = (addr << ADDR_tag_bit) >> (ADDR_tag_bit + ADDR_offset_bit);
    unsigned int tag = addr >> (ADDR_set_bit + ADDR_offset_bit);

    int i = 0;
    for(; i < way_num ; i++)
    {
	if((cache[index][i].tag == tag) && (cache[index][i].valid == 1))//cache hit
	{
	    cache[index][i].fre++;
	    if(instr == 'l')
		cache_load_num++;
	    else if(instr == 's')
		cache_store_num++;
	    cycle_num += cache_delay;
	    return ;
	}
    }

    //cache miss
    access_mem(instr);

    i = 0;
    for(; i < way_num ; i++)
    {
	if(cache[index][i].valid == 0) // exsit empty way
	{
	    cache[index][i].valid = 1;
	    cache[index][i].tag = tag;
	    cache[index][i].fre = 1;
	    return;
	}
    }

    if(replacepolicy == 1)//LRU
    {
    	/*TODO*/
    }
    else if(replacepolicy == 2)//Random
    {
    	/*TODO*/
    }

    return;
}

void access_mem(char instr)
{
    mem_access++;
    if(instr == 'l')
	mem_load_num++;
    else if(instr == 's')
	mem_store_num++;
    cycle_num += mem_delay;

    return;
}

