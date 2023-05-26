; Shubham Panchal
; https://shubham0204.github.io
; References: https://github.com/IamVaibhavsar/Second_Year_Lab_Assignments/tree/master/Microprocessor%20lab/nearFarProcedure

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

%macro file_open 1
mov  rax , 02         ; sys_file_open
mov  rdi , %1         ; file name
mov  rsi , 02         ; file access mode
mov  rdx , 0777       ; permissions
syscall
%endmacro

%macro file_read 3
mov  rax , 0
mov  rdi , %1
mov  rsi , %2
mov  rdx , %3
syscall 
%endmacro 

%macro file_close 1
mov  rax , 03
mov  rdx , %1
syscall
%endmacro

byte_hex_to_ascii:
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

print   line_break , 01
print   value      , 02
print   line_break , 01
ret



extern    proc_count_spaces
extern    proc_count_lines
extern    proc_count_char



global    count_char
global    count_lines
global    count_spaces
global    filesize
global    buffer
global    input_char



section .bss
filedesc       resb    01
filesize       resb    01
buffer         resb    200
count_spaces   resb    01   
count_lines    resb    01
count_char     resb    01

value                resb    01
input_char           resb    02
input_filename       resb    50



section .data
msg_count_spaces       db        "The number of spaces is"
len_count_spaces       equ       $-msg_count_spaces
msg_count_lines        db        "The number of lines is"
len_count_lines        equ       $-msg_count_lines
msg_count_char         db        "The frequency of given character is"
len_count_char         equ       $-msg_count_char
msg_input_char         db        "Enter char to find frequency:"
len_input_char         equ       $-msg_input_char
line_break             db        0xA



section .text

global _start
_start:

read        input_filename       ,     09

dec         rax
mov         byte[input_filename + rax] , 0
file_open   input_filename
mov         [filedesc]           ,   rax

file_read   [filedesc]   ,   buffer  ,  200
mov         [filesize]   ,   rax

call        proc_count_spaces
print       msg_count_spaces   ,   len_count_spaces
mov         rsi                ,   count_spaces
call        byte_hex_to_ascii

call        proc_count_lines
print       msg_count_lines  ,  len_count_lines
mov         rsi              ,  count_lines
call        byte_hex_to_ascii

print       msg_input_char   ,  len_input_char
read        input_char       ,  02
call        proc_count_char
print       msg_count_char   ,  len_count_char
mov         rsi              ,  count_char
call        byte_hex_to_ascii 

file_close  filedesc

exit