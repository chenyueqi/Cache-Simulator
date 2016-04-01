#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"common.h"

void access_cache(char instr, unsigned int addr);
void access_cache2(char instr, unsigned int addr);
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

    i = 0;
    j = 0;
    for(; i < set2_num ; i++)
	for(;j < way2_num ; j++)
	{
	    cache2[i][j].valid = 0;
	    cache2[i][j].tag = 0;
	    cache2[i][j].fre = 0;
	}

    cycle_num = 0;
    instr_num = 0;
    cycle_in_instr = 0;

    cache_access = 0;
    cache2_access = 0;
    mem_access = 0;

    cache_load_num = 0;
    cache2_load_num = 0;
    mem_load_num = 0;

    cache_store_num = 0;
    cache2_store_num = 0;
    mem_store_num = 0;

    return ;
}

void construct_cache(){init_cache();}

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

	unsigned int old_cycle_in_instr = cycle_in_instr;

	access_cache(instr, addr);

	instr_num++;
	cycle_num = cycle_num + cycle_in_instr - old_cycle_in_instr + delay;
    }

    fclose(trace);
    return 0;
}

void access_cache(char instr, unsigned int addr)
{
    cache_access++;
    cycle_in_instr += cache_delay;
    if(instr == 'l')
	cache_load_num++;
    else if(instr == 's')
	cache_store_num++;

    unsigned int offset = (addr << (ADDR_index_bit + ADDR_tag_bit)) >> (ADDR_index_bit + ADDR_tag_bit);
    unsigned int index = (associative == 3)?0:(addr << ADDR_tag_bit) >> (ADDR_tag_bit + ADDR_offset_bit);// in fully-associative, later could be wrong
    unsigned int tag = addr >> (ADDR_index_bit + ADDR_offset_bit);

    int i = 0;
    for(; i < way_num ; i++)
    {
	if((cache[index][i].tag == tag) && (cache[index][i].valid == 1))//cache hit
	{
	    cache[index][i].fre++;
	    return ;
	}
    }

    //cache miss
    access_cache2(instr , addr);

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

    int replaced_way = 0;

    if(replacepolicy == 1)//LRU
    {
	int i = 1;
	for(; i < way_num ; i++)
	    if(cache[index][i].fre < cache[index][replaced_way].fre)
		replaced_way = i;
    }
    else if(replacepolicy == 2)//Random
	replaced_way = rand() % way_num;

    cache[index][replaced_way].valid = 1;
    cache[index][replaced_way].tag = tag;
    cache[index][replaced_way].fre = 1;

    return;
}

void access_cache2(char instr, unsigned int addr)
{
    cache2_access++;
    cycle_in_instr += cache2_delay;
    if(instr == 'l')
	cache2_load_num++;
    else if(instr == 's')
	cache2_store_num++;

    unsigned int offset = (addr << (ADDR2_index_bit + ADDR2_tag_bit)) >> (ADDR2_index_bit + ADDR2_tag_bit);
    unsigned int index = (associative2 == 3)?0:(addr << ADDR2_tag_bit) >> (ADDR2_tag_bit + ADDR2_offset_bit);// in fully-associative, later could be wrong
    unsigned int tag = addr >> (ADDR2_index_bit + ADDR2_offset_bit);

    int i = 0;
    for(; i < way2_num ; i++)
    {
	if((cache2[index][i].tag == tag) && (cache2[index][i].valid == 1))//cache hit
	{
	    cache2[index][i].fre++;
	    return ;
	}
    }

    //cache miss
    access_mem(instr);

    i = 0;
    for(; i < way2_num ; i++)
    {
	if(cache2[index][i].valid == 0) // exsit empty way
	{
	    cache2[index][i].valid = 1;
	    cache2[index][i].tag = tag;
	    cache2[index][i].fre = 1;
	    return;
	}
    }

    int replaced_way = 0;

    if(replacepolicy2 == 1)//LRU
    {
	int i = 1;
	for(; i < way2_num ; i++)
	    if(cache2[index][i].fre < cache2[index][replaced_way].fre)
		replaced_way = i;
    }
    else if(replacepolicy2 == 2)//Random
	replaced_way = rand() % way2_num;

    cache2[index][replaced_way].valid = 1;
    cache2[index][replaced_way].tag = tag;
    cache2[index][replaced_way].fre = 1;

    return;
}

void access_mem(char instr)
{
    mem_access++;
    if(instr == 'l')
	mem_load_num++;
    else if(instr == 's')
	mem_store_num++;
    cycle_in_instr += mem_delay;

    return;
}
