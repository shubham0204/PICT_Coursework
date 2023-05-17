; Created with 💖 by Shubham Panchal
; https://shubham0204.github.io

%macro print 2
mov  rax , 01  ; sys_write
mov  rdi , 01  ; stdout - file descriptor
mov  rsi , %1  ; address of string to print
mov  rdx , %2  ; no. of bytes to print
syscall
%endmacro

%macro read  2
mov  rax , 00  ; sys_read
mov  rdi , 00  ; stdin - file descriptor
mov  rsi , %1  ; address where bytes are to be stored
mov  rdx , %2  ; no. of bytes to read
syscall
%endmacro

%macro exit  0
mov  rax , 60   ; sys_exit
mov  rdx , 00   
syscall 
%endmacro



byte_hex_to_ascii:
mov     bl   ,   [rsi]
mov     rdi  ,   value
mov     r9   ,   02h

add:
rol     bl   ,   04                  ; Rotate bl four times (swap nibbles)
mov     dl   ,   bl                  ; Move byte from bl to dl for conversion
and     dl   ,   0x0F                ; AND with 0x0F to make everything zero except for right-most nibble
cmp     dl   ,   09h                 ; Compare dl with 0x09
jbe   copydigit1                     ; Jump to copydigit1 if cmp result was below or equal
add     dl   ,   07h                 ; If there was no jump in above statement, add 07h to dl
copydigit1:
add     dl         ,  30h            ; Add 30h always
mov     [rdi]      ,  dl             ; Move converted digit in dl to location specified by rdi
inc     rdi                          ; Increment rdi (dest array pointer)
dec     r9                           ; Decrement r9
jnz     add                          ; If r9 is not equal to 0, jump to hex2ascii1 

print   value  ,  02
ret




section .bss
arg_count    resb    01
arg_input    resb    01
value        resb    01



section .text

global _start
_start:

pop     rcx
mov     byte[arg_count]   ,   cl
mov     rsi               ,   arg_count
call    byte_hex_to_ascii

pop     rbx
pop     rbx
pop     rbx
pop     rbx
mov     byte[arg_input]   ,   bl
mov     rsi               ,   arg_input
call    byte_hex_to_ascii

exit
