/**********************************/
// main.c
// main uefi boot entry

/**********************************/
// system includes

#include <efi.h>
#include <efilib.h>

/**********************************/
// local includes

#include "../common/bootinfo.h"

/**********************************/

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle,
                           EFI_SYSTEM_TABLE *SystemTable) {
  InitializeLib(ImageHandle, SystemTable);

  Print(L"UEFI boot\n");

  // Load kernel from file
  void *kernel_buffer = (void *)0x100000;

  load_elf(kernel_buffer);

  while (1)
    ;
  return EFI_SUCCESS;
}