#include <stdio.h>
#include "mem.h"
#include "mem7.c"

int main()
{
	Mem_Init(9999);

	int i = 0;
	void *ptr[5];
	for(int j = 0; j < 5; j++)
	{
		if(i == 0)
		{
			ptr[j] = Mem_Alloc(256);
			i++;
		}
		else if(i == 1)
		{
			ptr[j] = Mem_Alloc(258);
			i--;
		}
	}

	for(int j = 0; j < 5; j++)
	{
		Mem_Free(ptr[j] + 20);
	}
}
