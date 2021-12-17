ENTRY(loader) /* The name of the entry label */

SECTIONS {
    . = 0x00100000; /* The code should be loaded at 1MB */

    .text ALIGN (0x1000) : /* Align at 4KB */
    {
        *(.text) /* All text sections from all files */
    }

    .rodata ALIGN (0x1000) : /* Align at 4KB */
    {
        *(.rodata*) /* All read-only data sections from all files */
    }

    .data ALIGN (0x1000) : /* Align at 4KB */
    {
        *(.data) /* All data sections from all files */
    }

    .bss ALIGN (0x1000) : /* Align at 4KB */
    {
        *(COMMON) /* All COMMON sections from all files */
        *(.bss)   /* All bss sections from all files */
    }
}
