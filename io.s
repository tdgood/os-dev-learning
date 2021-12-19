global outb ; Make the label outb visible outside this file
global inb ; Make the label inb visible outside this file

; outb 
; send a byte to an I/O port
; 
; stack: [esp + 8] The data byte
;        [esp + 4] The I/O port
;        [esp    ] The return address
outb:
    mov al, [esp + 8] ; Move data to be sent to al reg
    mov dx, [esp + 4] ; Move data to be sent to dx reg
    out dx, al        ; Send the data to the I/O port
    ret               ; Return to calling function

; inb
; returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
;        [esp    ] The return address
inb:
    mov dx, [esp + 4] ; Move the address of the I/O port to the dx reg
    in al, dx         ; read a byte from the I/O port and store it in the al reg
    ret               ; Return the read byte
