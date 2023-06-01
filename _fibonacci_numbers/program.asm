; Program to generate Fibonacci numbers
; Author: Shubham Panchal - 21356
; https://shubham0204.github.io

%macro print 2
mov     rax     ,       01  ; sys_write
mov     rdi     ,       01  ; stdout - file descriptor
mov     rsi     ,       %1  ; address of string to print
mov     rdx     ,       %2  ; no. of bytes to print
syscall
%endmacro

%macro read  2
mov     rax     ,       00  ; sys_read
mov     rdi     ,       00  ; stdin - file descriptor
mov     rsi     ,       %1  ; address where bytes are to be stored
mov     rdx     ,       %2  ; no. of bytes to read
syscall
%endmacro

%macro exit  0
mov     rax     ,        60   ; sys_exit
mov     rdx     ,        00   
syscall 
%endmacro

asciitohex:
mov         bl      ,           00h
mov         rcx     ,           02h
next:
rol         bl      ,           04
mov         dl      ,           [rsi]
cmp         dl      ,           39h
jbe         update
sub         dl      ,           07h
update:
sub         dl      ,           30h
add         bl      ,           dl
inc         rsi
dec         rcx
jnz         next
ret

hextoascii:
mov         rcx     ,           02h
next1:
rol         bl      ,           04
mov         dl      ,           bl
and         dl      ,           0x0F
cmp         dl      ,           09h
jbe         update1
add         dl      ,           07h
update1:
add         dl      ,           30h
mov         [rdi]   ,           dl
inc         rdi
dec         rcx
jnz         next1
ret



section .data
msg1                 db       "Enter the number of Fibonacci numbers to generate" , 0xA
msg1len              equ       $-msg1
msg2                 db       "The Fibonacci numbers are" , 0xA
msg2len              equ       $-msg2
linebr               db        0xA



section .bss
number_ascii        resb            02
number_hex          resb            01
f_0                 resb            01
f_1                 resb            01
f_2                 resb            01



section .text

global      _start
_start:
 
; Prompt the user to enter the number of Fibonacci numbers to generate
print       msg1                ,       msg1len
read        number_ascii        ,       03

; Convert number_ascii to number_hex
mov         rsi                 ,       number_ascii 
call        asciitohex
br00:
mov         byte[number_hex]    ,       bl

print       msg2                ,       msg2len

; Print f_0 and f_1 (first two Fibonacci numbers)
mov         byte[f_0]           ,       00h
mov         bl                  ,       [f_0]
mov         rdi                 ,       number_ascii
call        hextoascii
print       number_ascii        ,       02
print       linebr              ,       01

mov         byte[f_1]           ,       01h    
mov         bl                  ,       [f_1]
mov         rdi                 ,       number_ascii
call        hextoascii
print       number_ascii        ,       02
print       linebr              ,       01

; Start the loop which generates the Fibonacci numbers
programloop:

; Compute f_2 by adding f_0 and f_1
mov         rax                 ,       [f_0]
add         rax                 ,       [f_1]
mov         [f_2]               ,       al

; Print f_2 (converting it to ASCII first)
mov         bl                  ,       [f_2]
mov         rdi                 ,       number_ascii
call        hextoascii
print       number_ascii        ,       02
print       linebr              ,       01

; Move f_1 to f_0 and f_2 to f_1
mov         bl                  ,       [f_1]
mov         [f_0]               ,       bl
mov         bl                  ,       [f_2]
mov         [f_1]               ,       bl

; Decrease number_hex by 1
dec         byte[number_hex]

; If number_hex is not 0, repeat the loop
jnz         programloop

exit