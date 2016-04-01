#include<stdio.h>
#include"common.h"

int write_conf(char* resultfile_name);
int write_result(char* trace_name ,char* resultfile_name);

int main(int argc ,char** argv)
{
    construct_cache();

    if(write_conf(argv[argc-1]))
    {
	fprintf(stderr , "Cache Simulation exits due to previous failures\n");
	return 1;
    }

    int i = 1;
    for( ; i < argc-1 ; i++) /*TODO to change to argc -1*/
    {
	if(run(argv[i]))
	{
	    fprintf(stderr , "Cache Simulation exits due to previous failures\n");
	    return 1;
	}
	if(write_result(argv[i] , argv[argc-1]))
	{
	    fprintf(stderr , "Cache Simulation exits due to previous failures\n");
	    return 1;
	}
	init_cache();
    }
    return 0;
}

/*write cache configuration information to result file*/
int write_conf(char* resultfile_name)
{
    FILE* conf = fopen(resultfile_name, "w");
    if(!conf)
    {
	fprintf(stderr, "Failed: result file could not be open %s %d\n" , __FILE__ , __LINE__);
	return 1;
    }

    fprintf(conf, "L1 cache | cache size: %dKB | " , cache_size);
    fprintf(conf, "cacheline size: %d bytes |  " , cacheline_size);
    fprintf(conf, "associative:  ");
    switch(associative)
    {
	case 1: fprintf(conf, "direct-mapeed\n"); break;
	case 2: fprintf(conf, "%d-way-set-associative | ", way_num); break;
	case 3: fprintf(conf, "fully-associative | "); break;
    }
    
    if(associative != 1)
    {
	switch(replacepolicy)
	{
	    case 1: fprintf(conf , "replacement policy: LRU\n");break;
	    case 2: fprintf(conf , "replacement policy: Random\n");break;
	}
    }

    /*victim cache configuration srite*/
    fprintf(conf, "victim cache | cache size: %dKB | " , cachev_size);
    fprintf(conf, "cacheline size: %d bytes |  " , cachelinev_size);
    fprintf(conf, "associative:  ");
    switch(associativev)
    {
	case 1: fprintf(conf, "direct-mapeed\n"); break;
	case 2: fprintf(conf, "%d-way-set-associative | ", wayv_num); break;
	case 3: fprintf(conf, "fully-associative | "); break;
    }
    if(associativev != 1)
    {
	switch(replacepolicyv)
	{
	    case 1: fprintf(conf , "replacement policy: LRU\n");break;
	    case 2: fprintf(conf , "replacement policy: Random\n");break;
	}
    }

    /*L2 cache configuration write*/
    fprintf(conf, "L2 cache | cache size: %dKB | " , cache2_size);
    fprintf(conf, "cacheline size: %d bytes |  " , cacheline2_size);
    fprintf(conf, "associative:  ");
    switch(associative2)
    {
	case 1: fprintf(conf, "direct-mapeed\n"); break;
	case 2: fprintf(conf, "%d-way-set-associative | ", way2_num); break;
	case 3: fprintf(conf, "fully-associative | "); break;
    }

    if(associative2 != 1)
    {
	switch(replacepolicy2)
	{
	    case 1: fprintf(conf , "replacement policy: LRU\n");break;
	    case 2: fprintf(conf , "replacement policy: Random\n");break;
	}
    }

    fprintf(conf , "\n");
    fclose(conf);
    return 0;
}

/*write simulation result of trace to result file respectively*/
int write_result(char* trace_name ,char* resultfile_name)
{
    FILE* result = fopen(resultfile_name, "a");
    if(!result)
    {
	fprintf(stderr, "Failed: result file could not be open %s %d\n" , __FILE__ , __LINE__);
	return 1;
    }

    fprintf(result, "%s\n" , trace_name);
    fprintf(result, "number of L1 cache accesses: %ld\n", cache_access);
    fprintf(result, "number of victim cache accesses: %ld\n", cachev_access);
    fprintf(result, "number of L2 cache accesses: %ld\n", cache2_access);
    fprintf(result, "number of memory accesses: %ld\n", mem_access);

    fprintf(result, "number of L1 cache loads: %ld\n", cache_load_num);
    fprintf(result, "number of victim cache loads: %ld\n", cachev_load_num);
    fprintf(result, "number of L2 cache loads: %ld\n", cache2_load_num);
    fprintf(result, "number of memory loads: %ld\n", mem_load_num);

    fprintf(result, "number of L1 cache stores: %ld\n", cache_store_num);
    fprintf(result, "number of victim cache stores: %ld\n", cachev_store_num);
    fprintf(result, "number of L2 cache stores: %ld\n", cache2_store_num);
    fprintf(result, "number of memory stores: %ld\n", mem_store_num);

    fprintf(result, "average L1 cache hit rate: %f\n", ((float)cache_access-(float)cachev_access-(float)cache2_access-(float)mem_access)/(float)instr_num);
    fprintf(result, "average victim cache hit rate: %f\n", (float)cachev_hit/(float)cachev_access);
    fprintf(result, "average L2 cache hit rate: %f\n", ((float)cache2_access-(float)mem_access)/((float)cache2_access));

    fprintf(result, "L1 cache hit rate for loads: %f\n", ((float)cache_load_num-(float)cachev_load_hit-(float)cachev_load_num-(float)cache2_load_num-(float)mem_load_num)/((float)cache_load_num));
    fprintf(result, "average victim cache hit rate: %f\n", (float)cachev_load_hit/(float)cachev_load_num);
    fprintf(result, "L2 cache hit rate for loads: %f\n", ((float)cache2_load_num-(float)mem_load_num)/((float)cache2_load_num));

    fprintf(result, "L1 cache hit rate for stores: %f\n", ((float)cache_store_num-(float)cachev_store_hit-(float)cache2_store_num-(float)mem_store_num)/((float)cache_store_num));
    fprintf(result, "average victim cache hit rate: %f\n", (float)cachev_store_hit/(float)cachev_store_num);
    fprintf(result, "L2 cache hit rate for stores: %f\n", ((float)cache2_store_num-(float)mem_store_num)/((float)cache2_store_num));

    fprintf(result, "CPU time: %ld\n", cycle_num);
    fprintf(result, "CPU time in loads and stores: %ld\n", cycle_in_instr);
    fprintf(result, "CPI: %f\n", (float)cycle_in_instr/(float)instr_num);
    fprintf(result , "\n");

    /*TODO more cahce statistics info*/

    fclose(result);
    return 0;
}
