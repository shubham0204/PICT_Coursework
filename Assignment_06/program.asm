; Shubham Panchal
; https://shubham0204.github.io
; Reference: https://github.com/RohanDoshi21/SE_PICT_SEM4/blob/main/MP/Assignment6/program.asm

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

printcontents:
mov     bl   ,   [rsi]
mov     rdi  ,   value
mov     r9   ,   02h

add:
rol     bl   ,   04                  ; Rotate bl four times (swap nibbles)
mov     dl   ,   bl                  ; Move byte from bl to dl for conversion
and     dl   ,   0x0F                ; AND with 0x0F to make everything zero except for right-most nibble
cmp     dl   ,   09h                 ; Compare dl with 0x09
jbe   copydigit1                     ; Jump to copydigit1 if cmp result was below or equal
add     dl   ,   07h                 ; If there was no jump in above statement, add 07h to dl
copydigit1:
add     dl         ,  30h            ; Add 30h always
mov     [rdi]      ,  dl             ; Move converted digit in dl to location specified by rdi
inc     rdi                          ; Increment rdi (dest array pointer)
dec     r9                           ; Decrement r9
jnz     add                          ; If r9 is not equal to 0, jump to hex2ascii1 

print   value  ,  02

ret

; -------------------------------------------------------

section .data
msg1   db   "Protection mode enabled" , 0xA
len1   equ  $-msg1

msg2   db   "--- GDTR ---" , 0xA
len2   equ  $-msg2

msg3   db   "--- MSW ---" , 0xA
len3   equ  $-msg3

msg4   db   "--- LDTR ---" , 0xA
len4   equ  $-msg4

msg5   db   "--- IDTR ---" , 0xA
len5   equ  $-msg5

msg6   db   "--- TR ---" , 0xA
len6   equ  $-msg6

linebr db   0xA

; -------------------------------------------------------

section .bss
cr0_data          resb   002
gdtr_data         resb   010
ldtr_data         resb   002
idtr_data         resb   010
tr_data           resb   002
value             resb   002

; -------------------------------------------------------

section .text

global _start
_start:

task_01:                              ; 1. Check protection status
smsw   [cr0_data]
mov    ebx          ,  [cr0_data]
bt     ebx          ,  00
jc     protection_enable_message
jmp    task_02

protection_enable_message:
print  msg1  ,  len1

task_02:        
print    msg3   ,   len3                         
mov      rsi    ,   cr0_data + 02h    
call     printcontents
mov      rsi    ,   cr0_data                   
call     printcontents
print    linebr            ,  001

task_03:
print    msg2   ,   len2                                 
sgdt     [gdtr_data]
mov      rsi    ,   gdtr_data + 10h    
call     printcontents
mov      rsi    ,   gdtr_data + 09h    
call     printcontents
mov      rsi    ,   gdtr_data + 08h    
call     printcontents
mov      rsi    ,   gdtr_data + 07h    
call     printcontents
mov      rsi    ,   gdtr_data + 06h    
call     printcontents
mov      rsi    ,   gdtr_data + 05h    
call     printcontents
mov      rsi    ,   gdtr_data + 04h    
call     printcontents
mov      rsi    ,   gdtr_data + 03h                  
call     printcontents
mov      rsi    ,   gdtr_data + 02h    
call     printcontents
mov      rsi    ,   gdtr_data                   
call     printcontents
print    linebr             ,  001

task_04:             
print    msg4   ,   len4                       
sldt     [ldtr_data]
mov      rsi    ,   ldtr_data + 02h    
call     printcontents
mov      rsi    ,   ldtr_data                   
call     printcontents
print    linebr             ,  001

task_05:
print    msg5   ,   len5                                    
sidt     [idtr_data]
mov      rsi    ,   idtr_data + 10h    
call     printcontents
mov      rsi    ,   idtr_data + 09h    
call     printcontents
mov      rsi    ,   idtr_data + 08h    
call     printcontents
mov      rsi    ,   idtr_data + 07h    
call     printcontents
mov      rsi    ,   idtr_data + 06h    
call     printcontents
mov      rsi    ,   idtr_data + 05h    
call     printcontents
mov      rsi    ,   idtr_data + 04h    
call     printcontents
mov      rsi    ,   idtr_data + 03h                  
call     printcontents
mov      rsi    ,   idtr_data + 02h    
call     printcontents
mov      rsi    ,   idtr_data                   
call     printcontents
print    linebr             ,  001

task_06:
print    msg6   ,   len6                       
str     [tr_data]
mov      rsi    ,   tr_data + 02h    
call     printcontents
mov      rsi    ,   tr_data                   
call     printcontents
print    linebr             ,  001

exit


