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

section .data
; Positive number ex: 0456h, Negative number ex: F458h 
; We initialize this number as a word, as we'll store it in ax
num      dw      0xFFF6 , 0x0F78 , 0x0F23 , 0x0234        
msg1     db      "The count of positive and negative numbers is" , 0xA
len1     equ     $-msg1
msg2     db      0xA , "Positive Count" , 0xA
len2     equ     $-msg2
msg3     db      0xA , "Negative Count" , 0xA
len3     equ     $-msg3

section .bss
poscountascii  resb  02   ; array to store count of positive numbers in ASCII
negcountascii  resb  02   ; array to store count of negative numbers in ASCII

section .text

global _start
_start:

mov    r10    ,  04h   ; counter to loop through array `num`
mov    r8     ,  00h   ; count of positive numbers
mov    r9     ,  00h   ; count of negative numbers
mov    rsi    ,  num   ; Moving base address `num` to rsi

program:

mov    ax   ,  word[rsi]    ; Move num to al

; 1st Approach - Use the sign flag
; mov    bx   ,  0000h         ; Move 0000h to bl
; add    ax   ,  bx            ; Add al and bl, which changes the sign flag SF         
; js     incnegcount           ; Jump to message2 if the sign flag is SET i.e. the number in al is negative
; jmp    incposcount           ; else jump to message2

; 2nd approach - Use the carry flag
; rcl    ax   ,  01              ; Rotate left with carry will rotate al by 01 and the sign bit (MSB) is stored 
;                                ; in the carry flag
; jc     incnegcount             ; Jump to message2 if the carry flag is SET i.e. the number in al is negative
; jmp    incposcount             ; else jump to message2

; 3rd approach - Use BT (Bit test) instruction
; bt     ax    ,  15           ; Test the bit at 15tt position i.e. the sign bit (MSB)
; jc     incnegcount           ; The bit is transferred to the carry flag. 
;                              ; Jump to message2 if the carry flag is SET i.e. the number in ax is negative
; jmp    incposcount           ; Jump to message2 if the carry flag is SET i.e. the number in al is negative

incposcount:
inc    r8
add    rsi   ,  02h
dec    r10
jnz    program
jmp    exitprogram

incnegcount:
inc    r9
add    rsi   ,  02h
dec    r10
jnz    program
jmp    exitprogram

exitprogram:
print    msg1   ,  len1

print    msg2   ,  len2
mov      rbx    ,  r8
mov      rdi    ,  poscountascii
call     hextoascii
print    poscountascii , 02

print    msg3   ,  len3
mov      rbx    ,  r9
mov      rdi   ,   negcountascii
call     hextoascii
print    negcountascii , 02
exit

