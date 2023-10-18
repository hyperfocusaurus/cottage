#pragma once

#include <stdint.h>

static inline uint64_t mmin(void* addr)
{
    uint64_t ret = 0;
    asm volatile (
        "mov %0, [%1]"
        : "=r" (ret)
        : "r" (addr)
        : "memory"
    );
    return ret;
}

static inline void mmout(void* addr, uint64_t value)
{
    asm volatile (
        "mov [%0], %1"
        : : "r" (addr),
            "r" (value)
        : "memory"
    );
}
