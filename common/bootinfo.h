/**********************************/

#pragma once

/**********************************/
// system includes

#include <stdint.h>

/**********************************/
// macros

#define MAX_MEMORY_REGIONS 32

/**********************************/
// structs

typedef struct {
    uint64_t base;
    uint64_t length;
    uint32_t type;
} memory_region_t;

typedef struct {
    uint64_t framebuffer_base;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint32_t framebuffer_pitch;

    uint32_t memory_region_count;
    memory_region_t memory_regions[MAX_MEMORY_REGIONS];
} boot_info_t;
