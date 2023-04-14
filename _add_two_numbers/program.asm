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


; -------------------------------------------------------

section .data
msg1  db  "Enter 1st number" , 0xA
len1  equ  $-msg1
msg2  db  "Enter 2nd number" , 0xA
len2  equ  $-msg2
msg3  db  "Sum is" , 0xA
len3  equ  $-msg3

; -------------------------------------------------------

section .bss
ascii_num1  resb  2    ;    8-bit operand 1 (represented with two digits in HEX)
ascii_num2  resb  2    ;    8-bit operand 2 (represented with two digits in HEX)
ascii_sum   resb  2    ;    8-bit result

; -------------------------------------------------------

section .text
global _start
_start:

print  msg1        ,  len1
read   ascii_num1  ,  02

xor  bl  ,  bl
mov  cl  ,  02h
mov  rsi ,  ascii_num1

f1:
rol  bl  ,  04
mov  al  ,  [rsi]
cmp  al  ,  39h
jbe  f2
sub  al  ,  07h
f2:
sub  al  ,  30h
add  bl  ,  al
inc  rsi
dec  cl
jne  f1

print  msg2        ,  len2
read   ascii_num2  ,  02

xor  bl  ,  bl
mov  cl  ,  02h
mov  rsi ,  ascii_num2

f3:
rol  bl  ,  04
mov  al  ,  [rsi]
cmp  al  ,  39h
jbe  f4
sub  al  ,  07h
f4:
sub  al  ,  30h
add  bl  ,  al
inc  rsi
dec  cl
jne  f3


exit