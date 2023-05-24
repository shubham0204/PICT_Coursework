; 0 -> read
; 1 -> write
; 2 -> read + write    access 

; file open
; rax -> 2
; rdi -> filename
; rsi -> 2
; rdx -> 0777h

; rax -> file descriptor

; file read
; rax -> 0
; rdi -> file descriptor
; rsi -> buffer
; rdx -> buffer size

; rax -> num bytes read OR file size


; file close 
; rax -> 3
; rdx -> file descriptor

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
mov  rdx , 0777o       ; permissions
syscall
%endmacro

%macro file_read 3
mov  rax , 0
mov  rdi , %1
mov  rsi , %2
mov  rdi , %3
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

print   value  ,  02
ret



section .bss
filedesc     resb    01
filesize     resb    01
buffer       resb    100
value        resb    01
char         resb    01
filename     resb    64


section .data
filename_const       db     "test.txt"
buffer_size    db     100



section .text

global _start
_start:

pop rcx
pop rcx
pop rcx 
mov         [filename]  ,  rcx
file_open   filename
br01:
mov    [filedesc]   ,   rax

file_read   filedesc  ,  buffer  ,  buffer_size

mov    [filesize]   ,   rax

mov    bl           ,   byte[filedesc + 4]
mov    [char]       ,   bl
mov    rsi          ,   char
print  char         ,   01

file_close  filedesc

exit