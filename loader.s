global loader ; The entry symbol for ELF

extern kmain ; Function 'kmain' is implemented elsewhere (kmain.c in our case)

MAGIC_NUMBER equ 0x1BADB002 ; Define the magic number constant
FLAGS equ 0x0               ; multiboot flags
CHECKSUM equ -MAGIC_NUMBER  ; Calculate the checksum
                            ; (magic number + flags + checksum should equal 0)

KERNEL_STACK_SIZE equ 4096 ; Define the kernel stack size in bytes

section .bss               ; Start of the bss section
align 4                    ; Align at 4 bytes
kernel_stack:              ; Label points to the beginning of the memory
    resb KERNEL_STACK_SIZE ; Reserve stack for the kernel

section .text       ; Start of the text (code) section
align 4             ; Align at 4 bytes
    dd MAGIC_NUMBER ; Write the magic number to the machine code
    dd FLAGS        ; Write the flags to the machine code
    dd CHECKSUM     ; Write the checksum to the machine code

mov esp, kernel_stack + KERNEL_STACK_SIZE ; Point esp to the start of the stack
                                          ; (end of memory area since stack
                                          ; grows backwards)

loader:        ; The loader label (defined as entry point in the linker script)
    call kmain ; Call kmain in kmain.c

.loop:
    jmp .loop ; Loop forever
