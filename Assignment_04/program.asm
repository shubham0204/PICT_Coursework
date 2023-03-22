; 21356 - Shubham Panchal
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

asciitohex:
mov   bl  ,  00h
mov   rcx ,  02h
next:
rol   bl  ,  04
mov   dl  ,  [rsi]
cmp   dl  ,  39h
jbe   update
sub   dl  ,  07h
update:
sub   dl  ,  30h
add   bl  ,  dl
inc   rsi
dec   rcx
jnz   next
ret

hextoascii:
mov   rcx  ,  02h
next1:
rol   bl   ,  04
mov   dl   ,  bl
and   dl   ,  0x0F
cmp   dl   ,  09h
jbe   update1
add   dl   ,  07h
update1:
add   dl   ,  30h
mov  [rdi] ,  dl
inc   rdi
dec   rcx
jnz   next1
ret
 
; -------------------------------------------------------

section .data
msg1     db   "Enter 1st number" , 0xA
len1     equ  $-msg1
msg2     db   "Enter 2nd number" , 0xA
len2     equ  $-msg2
msg3     db   "Result is" , 0xA
len3     equ  $-msg3
msg4     db   0xA , "Options are 0 -> Add, 1 -> Subtract, 2 -> Multiply, 3 -> Divide" , 0xA
len4     equ  $-msg4

; -------------------------------------------------------

section .bss
num1ascii     resb    02
num2ascii     resb    02
num1hex       resb    01
num2hex       resb    01
optionascii   resb    01
optionhex     resb    01
reshex        resb    01
resascii      resb    02

; -------------------------------------------------------

section .text

global _start
_start:

print    msg1       ,  len1
read     num1ascii  ,  03

print    msg2       ,  len2
read     num2ascii  ,  03

mov      bl    ,  00h
mov      rsi   ,  num1ascii
call     asciitohex
mov      [num1hex]  ,  bl

mov      bl    ,  00h
mov      rsi   ,  num2ascii
call     asciitohex
mov      [num2hex]  ,  bl

programloop:
print    msg4        ,  len4
read     optionascii ,  02
mov      bl    ,  byte[optionascii]
sub      bl    ,  30h
cmp      bl    ,  00h
jz       add
cmp      bl    ,  01h
jz       subtract
cmp      bl    ,  02h
jz       multiply
cmp      bl    ,  03h
jz       divide

add:
mov      al    ,  byte[num1hex]
mov      bl    ,  byte[num2hex]
add      al    ,  bl
mov   [reshex] ,  al
jmp      printres

subtract:
mov      al    ,  byte[num1hex]
mov      bl    ,  byte[num2hex]
sub      al    ,  bl
mov   [reshex] ,  al
jmp      printres

multiply:
mov      al    ,  byte[num1hex]
mov      bl    ,  byte[num2hex]
mul      bl
mov   [reshex] ,  al
jmp      printres

divide:
mov      al    ,  byte[num1hex]
mov      bl    ,  byte[num2hex]
div      bl
mov   [reshex] ,  al
jmp      printres

printres:
print    msg3       ,  len3
mov      bl    ,  [reshex]
mov      rdi   ,  resascii
call     hextoascii
print    resascii   ,  02
jmp      programloop

exit