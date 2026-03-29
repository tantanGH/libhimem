#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <x68k/iocs.h>
#include <x68k/dos.h>
#include "himem.h"

//
//  allocate high memory block
//
void* himem_malloc(size_t size) {

    struct iocs_regs in_regs = { 0 };
    struct iocs_regs out_regs = { 0 };

    in_regs.d0 = 0xF8;      // IOCS _HIMEM
    in_regs.d1 = 1;         // HIMEM_MALLOC
    in_regs.d2 = size;

    _iocs_trap15(&in_regs, &out_regs);

    uint32_t rc = out_regs.d0;

    return (rc == 0) ? (void*)out_regs.a1 : NULL;
}

//
//  allocate high memory block for array
//
void* himem_calloc(size_t count, size_t size) {

    struct iocs_regs in_regs = { 0 };
    struct iocs_regs out_regs = { 0 };

    in_regs.d0 = 0xF8;      // IOCS _HIMEM
    in_regs.d1 = 6;         // HIMEM_CALLOC
    in_regs.d2 = count;
    in_regs.d3 = size;

    _iocs_trap15(&in_regs, &out_regs);

    uint32_t rc = out_regs.d0;

    return (rc == 0) ? (void*)out_regs.a1 : NULL;
}

//
//  free high memory block
//
void himem_free(void* ptr) {
    
    struct iocs_regs in_regs = { 0 };
    struct iocs_regs out_regs = { 0 };

    in_regs.d0 = 0xF8;      // IOCS _HIMEM
    in_regs.d1 = 2;         // HIMEM_FREE
    in_regs.d2 = (size_t)ptr;

    _iocs_trap15(&in_regs, &out_regs);
}

//
//  get high memory total available size
//
size_t himem_getsize() {

    struct iocs_regs in_regs = { 0 };
    struct iocs_regs out_regs = { 0 };

    in_regs.d0 = 0xF8;          // IOCS _HIMEM
    in_regs.d1 = 3;             // HIMEM_GETSIZE

    _iocs_trap15(&in_regs, &out_regs);
  
    return out_regs.d0;
}

//
//  resize high memory block
//
int32_t himem_resize(void* ptr, size_t size) {

    struct iocs_regs in_regs = { 0 };
    struct iocs_regs out_regs = { 0 };

    in_regs.d0 = 0xF8;          // IOCS _HIMEM
    in_regs.d1 = 4;             // HIMEM_RESIZE
    in_regs.d2 = (size_t)ptr;
    in_regs.d3 = size;

    _iocs_trap15(&in_regs, &out_regs);
  
    return out_regs.d0;
}

//
//  check high memory service availability
//
int32_t himem_isavailable() {
  int32_t v = (int32_t)_dos_intvcg(0x1f8);
  return (v < 0 || (v >= 0xfe0000 && v <= 0xffffff)) ? 0 : 1;
}