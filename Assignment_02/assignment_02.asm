section .bss
mess resb 25

section .data
strmaxlen db 100

section .text
global _start
_start:
mov rsi , mess
strloop:
mov rax , 00
mov rdi , 00
mov rdx , 1
syscall
cmp rsi , 2Ch
je  print
add rsi , 1
jmp strloop

print:

mov rax , 01
mov rdi , 01
mov rsi , mess
mov rdx , 5
syscall

mov rax , 60
mov rdx , 00
syscall