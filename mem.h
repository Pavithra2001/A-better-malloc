#ifndef _MEM_H_
#define _MEM_H_

int Mem_Init(int sizeOfRegion);
void *Mem_alloc(int size);
int Mem_Free(void *ptr);
void* Mem_IsValid(void *ptr);
//size_t Mem_GetSize(struct block *ptr);

#endif



