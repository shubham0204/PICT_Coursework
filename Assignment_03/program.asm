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

section .bss   ; bss -> Block Started by Symbol - uninitialized variables
numsascii   resb  10
numshex     resb  10

; -------------------------------------------------------

section .data  ; data -> Initialized variables
msg1   db   "Enter five numbers" , 0xA           ; 0xA stands for line break
len1   equ  $-msg1                               ; Length of msg1 excluding trailing null character

; -------------------------------------------------------

section .text  ; text -> instructions

global _start: ; address from where program starts
_start:

print  msg1      , len1  
read   numsascii , 10

mov   rsi  ,  numsascii
mov   rcx  ,  10       

nums_ascii_loop:              ; ASCII to HEX conversion
rol   bl  ,  04
mov   al  ,  [rsi]
cmp   al  ,  09h
jbe   sub_30
sub   al  ,  07h
sub_30:
sub   al  ,  30h
add   bl  ,  al
inc   rsi
inc   rsi
dec   rcx
jnz   nums_ascii_loop

mov   rsi  ,  numsascii
mov   rcx  ,  10


exit






