; Shubham Panchal
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



factorial:
xor     rax  , rax                   ; Reset all GPRs
xor     rbx  , rbx
xor     rcx  , rcx
xor     rdx  , rdx

mov     cl   , [arg_input]           ; Move the input number to cl

push_num:
push    rcx                          ; Push the number to the stack
dec     rcx                          ; Decrement the number by 1
jnz     push_num                     ; Repeat if the number in rcx is not zero

mov     cl  ,  [arg_input]           ; Reinitialize counter to the input number
mov     bl  ,  01h                   ; bl holds the final output - product of all numbers
                                     ; i.e. the factorial

pop_num:
pop     rax                          ; pop the top element of the stack in rax
mul     rbx                          ; multiply with bl (rbx)
mov     bl  ,  al                    ; move the resulting product in bl (product is stored in rax)
dec     rcx                          ; decrement counter
jnz     pop_num                      ; if counter is not zero, repeat the process
ret



section .bss
arg_count    resb    01
arg_input    resb    01
value        resb    01
argv         resb    64
fact_output  resb    01



section .data
num           db     05h
line_br       db     0Ah


section .text

global _start
_start:

pop     rbx                            ; stores argc in rbx
pop     rbx                            ; stores the address of first argument in rbx i.e. argv[0]
pop     rbx                            ; stores the address of second argument in rbx i.e. argv[1]
mov     rdx             ,   00h
mov     dl              ,   [ rbx ]    ; fetch value from argv[1] and store in dl
sub     dl              ,   30h        ; subtract 30h from dl to convert ASCII to hex
mov     byte[arg_input] , dl           ; move dl to arg_input
print   arg_input       , 01           ; print arg_input
print   line_br         , 01

call    factorial                         ; call factorial procedure
mov     byte[fact_output] , bl            ; output is stored in bl, move it to fact_output
mov     rsi               , fact_output   ; HEX to ASCII conversion for fact_output
call    byte_hex_to_ascii
print   fact_output       , 02            ; print the factorial

exit
