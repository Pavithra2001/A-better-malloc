#include <stdio.h>
#include "mem.h"
#include "mem9.c"

int main()
{
	Mem_Init(9999);

	void *ptr1[5];
	for(int i=0; i < 5; i++)
	{
		int num = (rand() % (256 - 8 +1)) + 8;
		ptr1[i]=Mem_Alloc(num);
	}

	for(int j = 0; j < 5; j++)
	{
		Mem_Free(ptr1[j]);
	}
}
