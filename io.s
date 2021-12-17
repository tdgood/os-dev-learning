global outb ; Make the label outb visible outside this file

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
