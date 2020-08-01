# A-better-malloc
Paper - http://pages.cs.wisc.edu/~dusseau/Classes/CS537-F07/Projects/P3/index.html

I have created a memory allocator which is similar to malloc. However the memory free function is optimizzed.
In this implementaion of free, the parameter can be any pointer belonging to the address space of the previous allocated memory.
I have implemented four different allocation policy 

1. First Fit
2. Best Fit
3. Worst Fit
4. Next Fit

The functions implemented are:
1. int Mem_Init(int sizeOfRegion) - Mem_Init is called one time by the process. 
sizeOfRegion is the number of bytes that is requested from the OS using mmap. 
It is rounded up to an amount so that the memory is requested in units of the page size.

2. void *Mem_Alloc(int size): Mem_Alloc() is similar to the library function malloc(). 
Mem_Alloc takes as input the size in bytes of the object to be allocated and returns a pointer to the start of that object. 
The function returns NULL if there is not enough free space within sizeOfRegion allocated by Mem_Init to satisfy this request.

3. int Mem_Free(void *ptr): Mem_Free frees the memory object that ptr falls within. 
Just like with the standard free(), if ptr is NULL, then no operation is performed. 
The function returns 0 on success and -1 if ptr does not fall within the currently allocated object.
It also includes the case where the object was already freed with Mem_Free.

4. void * Mem_IsValid(void *ptr): This function returns the head of the current region if ptr 
falls within a currently allocated object and NULL if it does not.



