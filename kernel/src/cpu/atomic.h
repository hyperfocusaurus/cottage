#pragma once

#include <stdint.h>

#define atomic_load(x) _Generic((x), \
        uint64_t*: atomic_load64, \
        uint32_t*: atomic_load32, \
        uint16_t*: atomic_load16, \
        uint8_t*: atomic_load8, \
        default: atomic_load64 \
            )(x)

#define atomic_inc(x) _Generic((x), \
        uint64_t: atomic_inc64, \
        uint32_t: atomic_inc32, \
        uint16_t: atomic_inc16, \
        uint8_t: atomic_inc8, \
        default: atomic_inc64 \
)

inline uint64_t atomic_inc64(uint64_t* var)
{
    uint64_t diff = 1;

    asm volatile(
        "lock\n"
        "xaddq %1, %0"
        : "+m" (*var),
         "+r" (diff)
         : : "memory"
    );

    return diff;
}

inline uint32_t atomic_inc32(uint32_t* var)
{
    uint32_t diff = 1;

    asm volatile(
        "lock\n"
        "xaddl %1, %0"
        : "+m" (*var),
         "+r" (diff)
         : : "memory"
    );

    return diff;
}

inline uint16_t atomic_inc16(uint16_t* var)
{
    uint16_t diff = 1;

    asm volatile(
        "lock\n"
        "xaddw %1, %0"
        : "+m" (*var),
         "+r" (diff)
         : : "memory"
    );

    return diff;
}

inline uint8_t atomic_inc8(uint8_t* var)
{
    uint8_t diff = 1;

    asm volatile(
        "lock\n"
        "xaddb %1, %0"
        : "+m" (*var),
         "+r" (diff)
         : : "memory"
    );

    return diff;
}

inline uint64_t atomic_load64(uint64_t* var)
{
    uint64_t ret = 0;
    asm volatile (
        "lock  \n"
        "xaddq %1, %0"
        : "+m" (*var)
        : "r" (ret)
    );
    return ret;
}

inline uint32_t atomic_load32(uint32_t* var)
{
    uint32_t ret = 0;
    asm volatile (
        "lock \n"
        "xaddl %1, %0"
        : "+m" (*var)
        : "r" (ret)
    );
    return ret;
}

inline uint16_t atomic_load16(uint16_t* var)
{
    uint16_t ret = 0;
    asm volatile (
        "lock \n"
        "xaddw %1, %0"
        : "+m" (*var)
        : "r" (ret)
    );
    return ret;
}

inline uint8_t atomic_load8(uint8_t* var)
{
    uint8_t ret = 0;
    asm volatile (
        "lock \n"
        "xaddb %1, %0"
        : "+m" (*var)
        : "r" (ret)
    );
    return ret;
}