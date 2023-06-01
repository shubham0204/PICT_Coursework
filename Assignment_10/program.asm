; Shubham Panchal
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
mov         bx      ,       00h
mov         rcx     ,       04h
next:
rol         bx      ,       04
mov         dl      ,       00h
mov         dl      ,       [rsi]
cmp         dl      ,       39h
jbe         update
sub         dl      ,       07h
update:
sub         dl      ,       30h
and         dl      ,       0Fh
add         bl      ,       dl
inc         rsi
dec         rcx
jnz         next
ret

hextoascii:
mov         rcx     ,       02h
next1:
rol         bl      ,       04
mov         dl      ,       bl
and         dl      ,       0x0F
cmp         dl      ,       09h
jbe         update1
add         dl      ,       07h
update1:
add         dl      ,       30h
mov         [rdi]   ,       dl
inc         rdi
dec         rcx
jnz         next1
ret


array_hex_to_ascii:
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
jnz     array_hex_to_ascii           ; If r9 is not equal to 0, jump to array_hex_to_ascii 
                                     ; (this will happen two times for each digit)
mov     r9         ,  02h            ; Reinitialize r9 to 02h
mov     byte[rdi]  ,  20h            ; Add line break to show output on different lines
inc     rdi                          ; Increment rdi
inc     rsi                          ; Increment rsi
mov     bl         ,  [rsi]          ; Move next number in bl for conversion
dec     rcx                          ; Decrement array counter 
jnz     array_hex_to_ascii           ; Jump if rcx is not zero
ret



section .data
msg1                db          "Enter 4-digit hex number" , 0xA
len1                equ         $-msg1


section .bss
num_hex_ascii       resb            04
num_hex             resw            02
num_bcd_hex         resb            05
num_bcd_ascii       resb            15
quot                resw            01
num_hex_output      resw            01
num_hex_output_ascii       resb            08

section .text

global      _start
_start:

print           msg1                ,       len1
read            num_hex_ascii       ,       05
mov             rsi                 ,       num_hex_ascii
call            asciitohex
mov             [num_hex]           ,       bx


mov             rcx                 ,       05h
mov             rbx                 ,       00h
mov             bx                  ,       0Ah
mov             rdi                 ,       num_bcd_hex
mov             rax                 ,       00h
mov             ax                  ,       word[num_hex]
loop1:
mov             rdx                 ,       00h
div             bx
mov             word[quot]          ,       ax
mov             [rdi]               ,       dl
mov             ax                  ,       word[quot]
inc             rdi
dec             rcx
jnz             loop1

mov   rcx  , 05h                    
mov   r9   , 02h                    
mov   rsi  , num_bcd_hex                    
mov   rdi  , num_bcd_ascii              
mov   bl   , byte[num_bcd_hex]              
call  array_hex_to_ascii
print num_bcd_ascii                 ,       15

mov             rsi                 ,       num_bcd_hex
mov             rax                 ,       01h
mov             rcx                 ,       05h
mov             rbx                 ,       00h
mov             rdx                 ,       00h
loop2:
mov             bx                  ,       00h
mov             bx                  ,       word[rsi]
mul             bx
add             [num_hex_output]    ,       ax
mov             bx                  ,       0Ah
mul             bx
mov             bx                  ,       ax
add             rsi                 ,       02h
dec             rcx
jnz             loop2


mov             bl                  ,       00h
mov             rsi                 ,       [num_hex_output]

mov   rcx  , 02h                    
mov   r9   , 02h                    
mov   rsi  , num_hex_output                    
mov   rdi  , num_hex_output_ascii              
mov   bx   , word[num_hex_output]              
call  array_hex_to_ascii
print num_hex_output_ascii                 ,        08              

exit