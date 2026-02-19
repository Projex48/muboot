/**********************************/
// uefi_memory.c
// memory map extraction

/**********************************/
// system includes

#include <efi.h>
#include <efilib.h>

/**********************************/
// local includes

#include "../common/bootinfo.h"

/**********************************/

void get_memory_map(boot_info_t *boot_info) {
  UINTN map_size = 0;
  EFI_MEMORY_DESCRIPTOR *map = NULL;
  UINTN key;
  UINTN desc_size;
  UINT32 desc_version;

  uefi_call_wrapper(BS->GetMemoryMap, 5, &map_size, map, &key, &desc_size,
                    &desc_version);

  map_size += desc_size * 8;
  uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, map_size,
                    (void **)&map);

  uefi_call_wrapper(BS->GetMemoryMap, 5, &map_size, map, &key, &desc_size,
                    &desc_version);

  for (UINTN i = 0; i < map_size / desc_size; ++i) {
    EFI_MEMORY_DESCRIPTOR *desc =
        (EFI_MEMORY_DESCRIPTOR *)(uint8_t *)map + (i * desc_size);

    boot_info->memory_regions[i].base = desc->PhysicalStart;
    boot_info->memory_regions[i].length = desc->NumberOfPages * 4096;
    boot_info->memory_regions[i].type = desc->Type;

    boot_info->memory_region_count++;
  }
}