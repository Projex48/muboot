; Basic disk read helper

bits 16

global bios_read_sectors

bios_read_sectors:
    pusha
    mov ah, 0x02
    int 0x13
    jc disk_error
    popa
    ret

disk_error:
    hlt