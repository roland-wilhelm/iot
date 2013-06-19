#include "customHeap.h"


unsigned int CST_HEAP[CST_HEAP_SIZE / sizeof(int)] = {(CST_HEAP_SIZE / sizeof(int))}; //4k

void* cst_malloc(unsigned int i)
{
	unsigned int pointer = 0;
	unsigned int next = 0;
	if (i > CST_HEAP_SIZE - sizeof(unsigned int)) return 0;
	do {
		pointer = next;
		next = CST_HEAP[pointer];
		if (!(next & USE_MASK))
		{
			if (((next - pointer - 1) * 8) >= i)
			{
				CST_HEAP[pointer] = pointer + 1 + (i + sizeof(unsigned int) - 1)/sizeof(unsigned int);
				if (CST_HEAP[pointer] != next) CST_HEAP[CST_HEAP[pointer]] = next;
				CST_HEAP[pointer] = CST_HEAP[pointer] | USE_MASK;
				return &CST_HEAP[pointer + 1];
			}
		} else
		{
			next = next & ~USE_MASK;
		}
	} while (next < (CST_HEAP_SIZE / sizeof(int)));
	return 0;
}

void* cst_calloc(unsigned int i)
{
	int j = 0; //loop counter
	char* ret_pointer = cst_malloc(i);
	if (ret_pointer == 0) return 0;
	for (j = 0; j < i; j++) ret_pointer[j] = 0;
	return (void*) ret_pointer;
}

void cst_free(void* i)
{
	unsigned int position;
	unsigned int last;
	unsigned int next;
	
	last = 0;
	position = 0;
	next = 0;


	do
	{
		last = position;
		position = next;
		next = CST_HEAP[position & ~USE_MASK];

		if (((int) &CST_HEAP[(position & ~USE_MASK) + 1]) == ((int) i))
		{
			CST_HEAP[position & ~USE_MASK] = next & ~USE_MASK;
			if (!(last & ~USE_MASK))
			{
				CST_HEAP[last] = next & ~USE_MASK;
				position = last;
			}
			if (!(next & ~USE_MASK))
			{
				CST_HEAP[position & ~USE_MASK] = 
						(CST_HEAP[position & ~USE_MASK] & USE_MASK) & 
							CST_HEAP[next & ~USE_MASK];
			}
			return;
		}
	} while (((int) next) < (((int) & CST_HEAP[0]) + CST_HEAP_SIZE));
}
