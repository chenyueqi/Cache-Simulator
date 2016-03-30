#include<stdio.h>
#include<string.h>
#include"common.h"

void init_cache()
{
    int i = 0;
    int j = 0;
    for(; i < line_num ; i++)
	for(; j < way_num ; j++)
	    cache[i][j].valid = 0;

    cycle_num = 0;
    cache_access = 0;
    mem_access = 0;
    cache_load_num = 0;
    mem_load_num = 0;
    cache_store_num = 0;
    mem_store_num = 0;
    intr_num = 0;

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
	char* intr = strtok(buffer , " ");
	char* addr = strtok(NULL, " ");
	char* cycle = strtok(NULL , " \n");

	if(intr == NULL || addr == NULL || cycle == NULL)
	    break;

    }

    fclose(trace);
    return 0;
}
