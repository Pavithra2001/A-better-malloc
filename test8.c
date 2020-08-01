#include <stdio.h>
#include "mem.h"
#include "mem8.c"

int main()
{
	Mem_Init(9990);
	/*void *ptr = Mem_Alloc(256);
	printf("allocated memory: %p\n",ptr);
	Mem_Free(ptr + 20);*/

	void *ptr[5];
	for(int j = 0; j < 5; j++)
	{
		int num = (rand() % (256 - 24 + 1)) + 24;
		ptr[j] = Mem_Alloc(num);
	}

	/*for(int j=0;j<5;j++)
	{
		printf("ptr[j]: %p\n",ptr[j]);
	}*/

	for(int j = 0; j < 3; j++)
	{
		int re = Mem_Free(ptr[j]);
		if(re == 1)
			ptr[j] = 0;
	}

	void *ptr2[5];
	for(int j= 0; j < 5; j++)
	{
		int num = (rand() % (256 - 24 +1)) +24;
		ptr2[j] = Mem_Alloc(num);
	}

	for(int j = 0; j < 3; j++)
	{
		int re = Mem_Free(ptr2[j]);
		if(re == 1)
			ptr2[j] = 0;
	}

	for(int j = 0; j < 5; j++)
	{
		if(ptr[j] != 0)
		{
			Mem_Free(ptr[j]);
		}
		if(ptr2[j] != 0)
		{
			Mem_Free(ptr2[j]);
		}
	}
}
