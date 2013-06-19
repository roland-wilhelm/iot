#ifndef CST_HEAP_H
#define CST_HEAP_H
#define CST_HEAP_SIZE (4 << 10)
#define USE_MASK (1 << ((sizeof(unsigned int) * 8) - 1))

void* cst_malloc(unsigned int i);
void* cst_calloc(unsigned int i);
void cst_free(void* i);

#endif /* MY_HEAP_H */
