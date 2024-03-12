#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include <stdlib.h>

static unsigned long _s_mem_array_size = 256;
static void **_s_mem_array;

void *mem_alloc(unsigned long size);
void *mem_calloc(unsigned long count, unsigned long size);
void *mem_realloc(void *ptr, unsigned long size);
void mem_free(void *ptr);
void mem_free_all(void);

#endif // !MEM_UTILS_H
