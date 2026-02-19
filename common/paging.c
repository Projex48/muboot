
/**********************************/
// paging.c
// Simple 4-level paging for x86_64 architectures

/**********************************/
// system includes

#include <stdint.h>

/**********************************/
// macros

#define PAGE_PRESENT 1
#define PAGE_RW 2
#define PAGE_PS (1 << 7)

/**********************************/
// globals

uint64_t pml4[512] __attribute__((aligned(4096)));
uint64_t pdpt[512] __attribute__((aligned(4096)));
uint64_t pd[512] __attribute__((aligned(4096)));

/**********************************/

void setup_paging() {
  for (int i = 0; i < 512; i++)
    pd[i] = (i * 0x200000) | PAGE_PRESENT | PAGE_RW | PAGE_PS;

  pdpt[0] = (uint64_t)pd | PAGE_PRESENT | PAGE_RW;
  pml4[0] = (uint64_t)pdpt | PAGE_PRESENT | PAGE_RW;

  asm volatile("mov %0, %%cr3" ::"r"(pml4));
}
