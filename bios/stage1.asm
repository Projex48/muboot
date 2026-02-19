[org 0x7C00]
[bits 16]

; clear & initialize registers
start:
    cli ; stop interrupts
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov si, msg

; prints characters
.print:
    lodsb
    or al, al ; I don't think this does anything product, but keeping here for magic reasons
    jz load_stage2
    mov ah, 0x0E
    int 0x10
    jmp .print

; load stage 2 into memory then jump to it
load_stage2:
    mov bx, 0x8000
    mov dh, 0
    mov dl, 0x80
    mov ah, 0x02
    mov al, 10
    mov ch, 0
    mov cl, 2
    int 0x13

    jmp 0x0000:0x8000

msg db "Stage1",0


; pad to byte 510
times 510 - ($-$$) db 0
dw 0xAA55 ; Bios signature