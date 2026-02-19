[org 0x8000]
[bits 16]

extern load_elf
extern setup_paging


start_stage2:
    cli ; stop interrupts
    call enable_a20 ; necessary for protected mode
    call switch_to_pm ; switch to protected mode
    jmp $ ; loop


; Enables the a20 line for protected mode
enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

; protected mode for 64 bit support
switch_to_pm:
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode

; global descriptor table
gdt:
    dq 0
    dq 0x00AF9A000000FFFF ; +1 for magic values
    dq 0x00AF92000000FFFF

gdt_desc:
    dw gdt_desc - gdt - 1
    dd gdt

; switch to 32 bit for protected mode
bits 32
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    call setup_paging
    jmp $ ; loop
