section .data                            ; for initialized variables
M1   db   "Hello" , 0xA , "World" , 0xA  ; Declare variable M1 with db - define byte
L1   equ   $-M1                          ; equ denotes constant values

section .text               ; for writing instructions

global _start
_start:
mov           rax , 01      ; system call for write operation (must be moved in accumulator register)
mov           rdi , 01      ; file handle 01 is stdout
mov           rsi , M1      ; address of variable to output
mov           rdx , L1      ; no. of bytes
syscall

mov           rax , 60      ; system call for exit
mov           rdx , 00    
syscall
