%macro print 2
mov rax , 01   ; sys_write
mov rdi , 01
mov rsi , %1
mov rdx , %2
syscall
%endmacro

%macro read 2
mov rax , 00   ; sys_read
mov rdi , 00
mov rsi , %1
mov rdx , %2
syscall
%endmacro

section .data
msg  db  "Enter two-digit number:"
len  equ  $-msg
count1 db 02
count2 db 02
inputlen db 02

section .bss
num  resb  02
ans  resb  02

section .text
global _start
_start:

; Consider that the number "12" was entered by the user
; "12" is a string entered by the user. The ASCII code for each character (in hex) will be
; '1' -> 0x31 (occupies 1 byte)
; '2' -> 0x32 (occupies 1 byte)

print  msg , len   ; Print message
read   num , inputlen    ; Reading number, two digits would occupy two bytes of memory
                   ; Note: the number is stored in rsi
mov  rax , 00h     ; Contains ASCII values (from standard input or keyboard)
mov  rbx , 00h     ; Contains digit values (converted)

; Initially, rax and rbx contains zeros only
; rcx contains 0x02 for counter

back:
rol  rbx , 04h      ; rotate left
mov  al  , [rsi]    ; move value of address at rsi in al i.e. ASCII value of 1st char/digit from input
cmp  al  , 39h      ; Compare with 39h
jbe  next           ; Jump to label 'next' if result of cmp was below or equal
sub  al  , 07h      ; Subtract 07 if digit is greater than 39h
next:
sub  al  , 30h     ; Subtract 30h (always)
add  bx  , ax      ; Adding the resultant hex value (stored in al) to bx
inc  rsi           ; Incrementing rsi to next index
dec  byte[count1]  ; Decrementing counter
jnz  back          ; Jump to back if not zero above register, rcx, is not zero

mov  rbp , ans     ; mov ans base address to rbp

up:
rol  bl  , 04h         ; 
mov  dl  , bl          ;
and  dl  , 0Fh         ;
cmp  dl  , 09h         ;
jbe  next1             ;
add  dl  , 07h         ;
next1:
add  dl  , 30h         ;
mov  [rbp]  ,  dl      ;
inc  rbp               ;
dec  byte[count2]      ;
jnz  up                ;

print  ans , 02    ;

mov  rax , 60h      ; sys_exit
mov  rdx , 00h
syscall

