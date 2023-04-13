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

section .data
num   dw   0x0FF6                   ; Positive number ex: 0456h, Negative number ex: F458h 
                                    ; We initialize this number as a word, as we'll store it in ax
msg1  db  "The number is" , 0xA
len1  equ  $-msg1
msg2  db  "Positive" , 0xA
len2  equ  $-msg2
msg3  db  "Negative" , 0xA
len3  equ  $-msg3

section .text

global _start
_start:

program:
print  msg1  ,  len1

; 1st Approach - Use the sign flag
mov    ax   ,  [num]        ; Move num to al
mov    bx   ,  00h          ; Move 00h to bl
add    ax   ,  bx           ; Add al and bl, which changes the sign flag SF         
js     message2             ; Jump to message2 if the sign flag is SET i.e. the number in al is negative
jmp    message1             ; else jump to message2

; 2nd approach - Use the carry flag
; rcl    al   ,  01         ; Rotate left with carry will rotate al by 01 and the sign bit (MSB) is stored 
                            ; in the carry flag
; jc     message2           ; Jump to message2 if the carry flag is SET i.e. the number in al is negative
; jmp    message1           ; else jump to message2

; 3rd approach - Use BT (Bit test) instruction
bt     ax    ,  31          ; Test the bit at 31st position i.e. the sign bit (MSB)
jc     message2             ; The bit is transferred to the carry flag. 
                            ; Jump to message2 if the carry flag is SET i.e. the number in ax is negative
jmp    message1             ; Jump to message2 if the carry flag is SET i.e. the number in al is negative


message1:
print  msg2  ,  len2
jmp    exitprogram

message2:
print  msg3  ,  len3
jmp    exitprogram

exitprogram:
exit

