section .bss
num resb 85                              ; initialize array of 85 bytes

section .data
M1      db "Enter 5 64bit numbers" , 0xA   ; initialize string M1
L1      equ $-M1                           ; set constant L1 which equals size of M1
count1  db  05                            ; counter for input loop
count2  db  05                            ; counter for output loop

section .text
global _start
_start:

mov rax , 01   ; write call
mov rdi , 01   ; destination - standard o/p
mov rsi , M1   ; write string M1
mov rdx , L1   ; write L1 bytes
syscall

xor rsi , rsi  ; reset rsi
mov rsi , num  ; mov num to rsi

loop1:
mov rax , 00      ; system read call (sys_read)
mov rdi , 00      ; destination - standard i/p
mov rdx , 17      ; read 17 bytes
syscall
add rsi , 17      ; increment num by 17 bytes
dec byte[count1]  ; decrement counter (byte addressed)
jnz loop1         ; jump if flag register ZF = 0

mov rsi , num     ; mov num to rsi

loop2:
mov rax , 01      ; system write call (sys_write)
mov rdi , 01      ; destination - standard o/p
mov rdx , 17      ; write 17 bytes
syscall
add rsi , 17      ; add 17 bytes to rsi 
dec byte[count2]  ; decrement counter
jnz loop2         ; jump if flag register ZF = 0

mov rax , 60      ; system exit call (sys_exit)
mov rdx , 0       
syscall



