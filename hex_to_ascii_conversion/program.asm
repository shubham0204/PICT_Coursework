%macro print 2
mov rax , 01   ; sys_write
mov rdi , 01
mov rsi , %1
mov rdx , %2
syscall
%endmacro

%macro read 2
mov rax , 00    ; sys_read
mov rdi , 00
mov rsi , %1
mov rdx , %2
syscall
%endmacro

section .data
M1 db "Enter a two-digit number..." , 0xA
L1 equ $-M1
M2 db "The two-digit number is..." , 0xA
L2 equ $-M2
M3 db 2

section .bss
num  resb  2  ; Two digits -> Two bytes
ans  resb  2

section .text
global _start
_start:

; Consider that the number "12" was entered by the user
; "12" is a string entered by the user. The ASCII code for each character (in hex) will be
; '1' -> 0x31 (occupies 1 byte)
; '2' -> 0x32 (occupies 1 byte)

print  M1 , L1   ; Print message
read   M3 , 02    ; Reading number, two digits would occupy two bytes of memory
                   ; Note: the number is stored in rsi

mov  rax , 00h     ; Contains ASCII values (from standard input or keyboard)
mov  rbx , 00h     ; Contains digit values (converted)
mov  rcx , 02h     ; A counter stored in rcx

; Initially, rax and rbx contains zeros only
; rcx contains 0x02 for counter

back:
rol  bl , 04        ; rotate left 4 times
mov  al  , [rsi]    ; move value of address at rsi in al i.e. ASCII value of 1st char/digit from input
cmp  al  , 39h      ; Compare with 39h
jbe  next           ; Jump to label 'next' if result of cmp was below or equal
sub  al  , 07h      ; Subtract 07 if digit is greater than 39h

next:
sub  al  , 30h     ; Subtract 30h (always)
add  bl  , al      ; Adding the resultant hex value (stored in al) to bx
inc  rsi           ; Incrementing rsi to next index
dec  rcx           ; Decrementing counter
jnz  back          ; Jump to back if not zero above register, rcx, is not zero

print M2 , L2

mov  rsi , ans     ; mov ans base address to rbp
mov  rcx , 02h     ; reset counter to 0x02

up:
rol  bl  , 04          ; rotate left 4 times (i.e. swap nibbles)
mov  dl  , bl          ; copy byte from bl to dl
and  dl  , 0Fh         ; perform AND to 0x0F ( 0000 1111 in binary )
cmp  dl  , 09h         ; compare with 09h
jbe  next1             ; Jump to label 'next1' if result of cmp was below or equal
add  dl  , 07h         ; Add 07h if greater than 09h

next1:
add  dl  , 30h         ; Add 30h always
mov  [rsi]  ,  dl      ; copy byte from dl to location specified by rsi
inc  rsi               ; increment rsi index
dec  rcx               ; decrement counter
jnz  up                ; Go to 'up' label if rcx is not zero

print  ans , 2    ; Print the 'ans' array upto 2 bytes

mov  rax , 60      ; sys_exit
mov  rdx , 0
syscall

