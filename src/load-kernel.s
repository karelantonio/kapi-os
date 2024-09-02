; Just call the kernel.c file
    [bits 32]
    ;[org 0x1000]
    [extern kernel]
    global _entrypoint
_entrypoint:
    call kernel
    jmp $
