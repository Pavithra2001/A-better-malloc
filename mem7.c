#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "mem.h"
#include <stdlib.h>
#include<stddef.h>

struct block
{
	size_t size;
	int free;
	struct block *next;
};

struct block *head =NULL;
int callsToInit = 0;
int pageSize;
int totalSize;

int Mem_Init(int sizeOfRegion)
{
	totalSize = sizeOfRegion;
	printf("I'm calling: Mem_Init()\n");
	if(sizeOfRegion <= 0|| callsToInit >0)
		return -1;
	pageSize = getpagesize();
	printf("Page Size: %d\n",pageSize);
	if((sizeOfRegion % pageSize) != 0)
		sizeOfRegion += (pageSize- (sizeOfRegion % pageSize));
	printf("Size of Region: %d\n", sizeOfRegion);
	int fd = open("/dev/zero", O_RDWR);
	head = mmap(NULL, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if( head == MAP_FAILED)
		exit(1);
	head->size = sizeOfRegion;
	head->next = NULL;
	head->free = 1;
	close(fd);
	callsToInit++;
	return 0;
}

void split(struct block *fitting_slot,size_t size){
        struct block *new=(void*)((void*)fitting_slot+size+sizeof(struct block));
        new->size=(fitting_slot->size)-size-sizeof(struct block);
        new->free=1;
        new->next=fitting_slot->next;
        fitting_slot->size=size;
       // fitting_slot->free=0;
        fitting_slot->next=new;
}


void *Mem_Alloc(size_t size)
{

	int extra = size % 8;
	extra = (8 - extra) % 8;
	int rounded = size+extra;
	int wasted = rounded - size;

	struct block *curr;
	void *result;
	curr = head;
	int bestSize = 200000;
	while(curr)
	{
		if(curr->free == 0 || curr->size < size)
			curr = curr->next;
		else
		{
		//	printf("start\n");
			if(curr->size <= bestSize)
			{
				result = (void *)curr;
				bestSize = curr->size;
			}
			curr = curr->next;
		}
	}
	curr = (struct block *)result;
	split(curr, size);
	curr->free = 0;
	printf("allocated memory of size: %ld\n", curr->size);
	printf("wasted memory: %d\n",wasted);
	return result;
}

void* Mem_IsValid(void *ptr)
{
	struct block *curr = head;
	while(curr)
	{
		if(curr->free == 0)
		{
			if(ptr >= (void *)(char *)curr && ptr <= (void *)((char *)curr + curr->size))
			{
				return (void *)curr;
			}
		}
		curr = curr->next;
	}
}

int Mem_Free(void *ptr)
{
		struct block *curr = (struct block *)Mem_IsValid(ptr);
		if(curr)
		{
			curr->free = 1;	
			printf("freed block of size: %ld\n",curr->size);
			return 1;
		}
		else
			return -1;
}
