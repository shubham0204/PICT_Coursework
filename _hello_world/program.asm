; Created with 💖 by Shubham Panchal
; https://shubham0204.github.io

section .data                                           ; for initialized variables
message  db   "Hello World from Assembly! 🥳" , 0xA     ; db -> define byte and 0xA is a line break (\n)
len      equ  $-message                                 ; calculate length of message

section .text            ; contains instructions

global _start            ; like `main()` from C++
_start:

mov  rax  ,  01          ; 01 in rax indicates 'write' operation
mov  rdi  ,  01          ; 01 in rdi denotes standard output device (i.e. console)
mov  rsi  ,  message     ; rsi holds message to be displayed
mov  rdx  ,  len         ; rdi holds no. of bytes to be displayed, in this case, it is `len`
syscall                  ; call the system kernel to perform the operation

mov  rax  ,  60          ; initiate exit call (sys_exit) to indicate successful completion of program
mov  rdx  ,  00
syscall