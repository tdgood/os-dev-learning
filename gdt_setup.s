extern segmentation_load_gdt ; Make the label segmentation_load_gdt visible 
                             ; outside this file
extern segmentation_load_registers ; Make the label 
                                   ; segmentation_load_registers visible
                                   ; outside this file

; segmentation_load_gdt
; Load the global descriptor table (gdt)
;
; stack: [esp + 4] The starting address of the gdt struct
;        [esp    ] The return address
segmentation_load_gdt:
    lgdt [esp + 4] ; Load the gdt
    ret            ; Return to calling function

; segmentation_load_registers
; Loads ds, ss, es, fs, gs with kernel data segment offset (0x10) and
; uses a far jump to load cs with kernel code segment offset (0x08)
segmentation_load_registers:
    mov eax, 0x10
    mov ds, eax
    mov ss, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    jmp 0x08:flush_cs

flush_cs:
    ret
