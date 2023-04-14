; Created with 💖 by Shubham Panchal
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
num1ascii     resb    02        ; ASCII representation of num1 (2 chars -> 2 bytes)
num2ascii     resb    02        ; ASCII representation of num2 (2 chars -> 2 bytes)
num1hex       resb    01        ; Hex representation of num1
num2hex       resb    01        ; Hex representation of num2
optionascii   resb    01        ; ASCII representation of option (1 char -> 1 byte)
optionhex     resb    01        ; Hex representation of option
resascii      resb    02        ; ASCII representation of result (2 chars -> 2 bytes)
reshex        resb    01        ; Hex representation of result

; -------------------------------------------------------

section .text

global _start
_start:

print    msg1       ,  len1
read     num1ascii  ,  03       ; Read 3 bytes (including EOF character)

print    msg2       ,  len2
read     num2ascii  ,  03       ; Read 3 bytes (including EOF character)

mov      bl    ,  00h           ; reset bl
mov      rsi   ,  num1ascii     ; set rsi to address of num1ascii
call     asciitohex
mov      [num1hex]  ,  bl       ; move converted digit from bl to [num1hex]

mov      bl    ,  00h           ; reset bl
mov      rsi   ,  num2ascii     ; set rsi to address of num2ascii
call     asciitohex
mov      [num2hex]  ,  bl       ; move converted digit from bl to [num2hex]

programloop:
print    msg4        ,  len4
read     optionascii ,  02           ; read option from user (including EOF character)
mov      bl    ,  byte[optionascii]  ; move option (ascii) to bl
sub      bl    ,  30h                ; subtract 30h to get hex value
cmp      bl    ,  00h                ; compare with 00h
jz       add                         ; jump to 'add' if bl == 00h
cmp      bl    ,  01h
jz       subtract                    ; jump to 'subtract' if bl == 01h
cmp      bl    ,  02h
jz       multiply                    ; jump to 'multiply' if bl == 02h
cmp      bl    ,  03h
jz       divide                      ; jump to 'divide' if bl == 03h

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