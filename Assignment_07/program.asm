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



array_hex_to_ascii:
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
jnz     array_hex_to_ascii           ; If r9 is not equal to 0, jump to array_hex_to_ascii 
                                     ; (this will happen two times for each digit)
mov     r9         ,  02h            ; Reinitialize r9 to 02h
mov     byte[rdi]  ,  0xA            ; Add line break to show output on different lines
inc     rdi                          ; Increment rdi
inc     rsi                          ; Increment rsi
mov     bl         ,  [rsi]          ; Move next number in bl for conversion
dec     rcx                          ; Decrement array counter 
jnz     array_hex_to_ascii           ; Jump if rcx is not zero
ret



print_src_dist_arrays:
print   srcmsg  ,  srcmsglen         ; Printing the source array
mov   rcx  , 0Ah                     ; Counter for no. of digits to print
mov   r9   , 02h                     ; Counter for processing each digit two times
mov   rsi  , src                     ; Move `arr` to rsi (source array)
mov   rdi  , src_ascii                  ; Move `arrout` to rdi (destination array)
mov   bl   , byte[src]               ; Move first byte of [arr] to bl for hex2ascii conversion
call  array_hex_to_ascii
print src_ascii  ,  30

print   dstmsg  ,  dstmsglen         ; Printing the destination array
mov   rcx  , 0Ah                     ; Counter for no. of digits to print
mov   r9   , 02h                     ; Counter for processing each digit two times
mov   rsi  , dst                     ; Move `arr` to rsi (source array)
mov   rdi  , dst_ascii                  ; Move `arrout` to rdi (destination array)
mov   bl   , byte[dst]               ; Move first byte of [arr] to bl for hex2ascii conversion
call  array_hex_to_ascii
print dst_ascii  ,  30
ret



section .data
src        db    01h , 02h , 03h , 04h , 05h , 00h , 00h , 00h , 00h , 00h
dst        db    00h , 00h , 00h , 00h , 00h , 00h , 00h , 00h , 00h , 00h
msg        db    "Enter Option:" , 0xA , "1 - Without String , 2 - With String, 3 - Without string overlapping , 4 - With string overlapping,  5 - Exit" , 0xA
msglen     equ   $-msg
srcmsg     db    "Source is:" , 0xA
srcmsglen  equ   $-srcmsg
dstmsg     db    "Destination is:" , 0xA
dstmsglen  equ   $-dstmsg



section .bss
opt         resb   02
src_ascii   resb   15
dst_ascii   resb   15  



section .text 

global _start
_start:

print   msg   ,   msglen

programloop: 
read    opt   ,   02
mov     bl    ,   byte[opt]
cmp     bl    ,   31h
jz      without_str
cmp     bl    ,   32h
jz      with_str
cmp     bl    ,   33h
jz      without_str_ovrlap
cmp     bl    ,   34h
jz      with_str_overlap
cmp     bl    ,   35h
jz      exitprogram

without_str:
mov     rsi   ,   src
mov     rdi   ,   dst
mov     rcx   ,   05h
copy_num:
mov     bl    ,   [rsi]
mov     [rdi] ,   bl
inc     rsi
inc     rdi
dec     rcx
jnz     copy_num
call    print_src_dist_arrays
jmp     programloop

with_str:
mov     rsi   ,   src
mov     rdi   ,   dst
mov     rcx   ,   05h
cld
rep     movsb
call    print_src_dist_arrays
jmp     programloop

without_str_ovrlap:
mov     rsi   ,   src
mov     rdi   ,   dst
add     rdi   ,   04h
mov     rcx   ,   05h
copy_num1:
mov     bl    ,   [rsi]
mov     [rdi] ,   bl
inc     rsi
inc     rdi
dec     rcx
jnz     copy_num1
call    print_src_dist_arrays
jmp     programloop

with_str_overlap:
mov     rsi   ,   src
mov     rdi   ,   dst
add     rdi   ,   04h
mov     rcx   ,   05h
cld
rep     movsb
call    print_src_dist_arrays
jmp     programloop

exitprogram:
exit
