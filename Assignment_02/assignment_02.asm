section .data
msg1  db  "Enter string: " , 0xA
msg2  db  "Enter length: " , 0xA
len1  equ  $-msg1
len2  equ  $-msg2

section .text
global _start
_start:

%macro print 2
mov rax , 01
mov rdi , 01
mov rsi , %1
mov rdx , %2
syscall
%endmacro

%macro read 2
mov rax , 00
mov rdi , 00
mov rsi , %1
mov rdx , %2
syscall
%endmacro

print msg1 , len1
print msg2 , len2

mov rax , 60
mov rdi , 00
syscall





