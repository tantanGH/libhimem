#ifndef __H_HIMEM__
#define __H_HIMEM__

#include <stdint.h>
#include <stddef.h>

void* himem_malloc(size_t size);
void* himem_calloc(size_t count, size_t size);
void himem_free(void* ptr);
size_t himem_getsize();
int32_t himem_resize(void* ptr, size_t size);
int32_t himem_isavailable(void);

#endif