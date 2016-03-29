#include"common.h"

void init_cache()
{
    int i = 0;
    for(; i < line_num;i++)
	cache[i].valid = 0;

    /*TODO recover some statistic information*/

    return ;
}

void construct_cache()
{
    init_cache();
}

void run(char* trace_name)
{
    /*TODO trace run*/

    return;
}
