/**********************************/
// elf_loader.c
// Minimal elf64 loader

/**********************************/
// system includes

#include <stdint.h>

/**********************************/
// local includes

#include "bootinfo.h"

/**********************************/
// macros

#define EI_NIDENT 16
#define PT_LOAD 1

/**********************************/
// structs

typedef struct {
  unsigned char e_ident[EI_NIDENT];
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  uint64_t e_entry;
  uint64_t e_phoff;
  uint64_t e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
} elf64_Ehdr;

typedef struct {
  uint32_t p_type;
  uint32_t p_flags;
  uint64_t p_offset;
  uint64_t p_vaddr;
  uint64_t p_paddr;
  uint64_t p_filesz;
  uint64_t p_memsz;
  uint64_t p_align;
} elf64_Phdr;

/**********************************/
// prototypes

extern void *memcpy(void *, const void *, unsigned long);
extern void *memset(void *, int, unsigned long);

/**********************************/

void load_elf(void *elf_data) {
  elf64_Ehdr *ehdr = (elf64_Ehdr *)elf_data;
  elf64_Phdr *phdr = (elf64_Phdr *)((uint8_t *)elf_data + ehdr->e_phoff);

  for (int i = 0; i < ehdr->e_phnum; ++i) {
    if (phdr[i].p_type != PT_LOAD)
      continue;

    memcpy((void *)phdr[i].p_paddr, (uint8_t *)elf_data + phdr[i].p_offset,
           phdr[i].p_filesz);

    memset((void *)(phdr[i].p_paddr + phdr[i].p_filesz), 0,
           phdr[i].p_memsz - phdr[i].p_filesz);
  }

  void (*entry)(boot_info_t *) = (void *)ehdr->e_entry;
  entry((boot_info_t *)0x7000);
}