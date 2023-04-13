; 21356 - Shubham Panchal
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

hextoascii:
mov   rcx  ,  02h
next1:
rol   bl   ,  04
mov   dl   ,  bl
and   dl   ,  0x0F
cmp   dl   ,  09h
jbe   update1
add   dl   ,  07h
update1:
add   dl   ,  30h
mov  [rdi] ,  dl
inc   rdi
dec   rcx
jnz   next1
ret

section .data
; Positive number ex: 0456h, Negative number ex: F458h 
; We initialize this number as a word, as we'll store it in ax
num   dw   0x0FF6 , 0x0F78 , 0x0F23 , 0x0234        
msg1  db  "The count of positive and negative numbers is" , 0xA
len1  equ  $-msg1
msg2  db  "Positive" , 0xA
len2  equ  $-msg2
msg3  db  "Negative" , 0xA
len3  equ  $-msg3

section .bss
count1ascii  resb  02
count2ascii  resb  02

section .text

global _start
_start:

mov    r10    ,  04h
mov    r8     ,  00h
mov    r9     ,  00h
mov    rsi    ,  num
print  msg1  ,  len1

program:

; 1st Approach - Use the sign flag
mov    ax   ,  word[rsi]    ; Move num to al
; mov    bx   ,  0000h        ; Move 0000h to bl
; add    ax   ,  bx           ; Add al and bl, which changes the sign flag SF         
; js     message2             ; Jump to message2 if the sign flag is SET i.e. the number in al is negative
; jmp    message1             ; else jump to message2

; 2nd approach - Use the carry flag
; rcl    al   ,  01         ; Rotate left with carry will rotate al by 01 and the sign bit (MSB) is stored 
                            ; in the carry flag
; jc     message2           ; Jump to message2 if the carry flag is SET i.e. the number in al is negative
; jmp    message1           ; else jump to message2

; 3rd approach - Use BT (Bit test) instruction
bt     ax    ,  15          ; Test the bit at 15tt position i.e. the sign bit (MSB)
jc     message2             ; The bit is transferred to the carry flag. 
                            ; Jump to message2 if the carry flag is SET i.e. the number in ax is negative
jmp    message1             ; Jump to message2 if the carry flag is SET i.e. the number in al is negative


message1:
inc    r8
add    rsi   ,  02h
dec    r10
jnz    program
jmp    exitprogram

message2:
inc    r9
add    rsi   ,  02h
dec    r10
jnz    program
jmp    exitprogram

exitprogram:
mov      rbx    ,  r9
mov      rdi   ,  count1ascii
call     hextoascii
print    count1ascii , 02

mov      rbx    ,  r8
mov      rdi   ,  count2ascii
call     hextoascii
print    count2ascii , 02
exit

