%macro print 2
mov  rax , 01  ; sys_write
mov  rdi , 01  ; stdout - file descriptor
mov  rsi , %1  ; address of string to print
mov  rdx , %2  ; no. of bytes to print
syscall
%endmacro

%macro exit  0
mov  rax , 60   ; sys_exit
mov  rdx , 00   
syscall 
%endmacro

; -------------------------------------------------------

section .data
arr     db   01h , 52h , 03h , 05h , 04h

; -------------------------------------------------------

section .bss
arrout    resb  16
maxnumout resb  03

; -------------------------------------------------------

section .text

global _start
_start:


mov   rcx  , 05h                     ; Counter for no. of digits to print
mov   r9   , 02h                     ; asda

mov   rsi  , arr                     ; Move `arr` to rsi (source array)
mov   rdi  , arrout                  ; Move `arrout` to rdi (destination array)
mov   bl   , byte[arr]               ; Move first byte of [arr] to bl for hex2ascii conversion

hextoascii1:
rol     bl   ,   04                  ; Rotate bl four times (swap nibbles)
mov     dl   ,   bl                  ; Move byte from bl to dl for conversion
and     dl   ,   0x0F                ; AND with 0x0F to make everything zero except for right-most nibble
cmp     dl   ,   09h                 ; Compare dl with 0x09
jbe   copydigit1                     ; Jump to copydigit1 if cmp result was below or equal
add     dl   ,   07h                 ; If there was no jump in above statement, add 07h to dl
copydigit1:
add     dl         ,  30h            ; Add 30h always
mov     [rdi]      ,  dl             ; Move converted digit in dl to location specified by rsi
inc     rdi                          ; Increment rdi (dest array pointer)
dec     r9                           ; Decrement r9
jnz     hextoascii1
mov     r9         ,  02h
mov     byte[rdi]  ,  0xA
inc     rdi 
inc     rsi 
mov     bl         ,  [rsi]
dec     rcx
jnz     hextoascii1

mov     byte[rdi]  ,  0xA
inc     rdi

print arrout , 16

mov   rsi , arr
mov   al  , 0h                  ; Stores the current largest number 
mov   rcx , 05h                 ; Counter for iterating through the array

arrloop:
mov   bl  , [rsi]               ; Move element pointed by [rsi] to bl
cmp   bl  , al                  ; Compare current element (in bl) with al (current largest num)
jb    update                    ; If the bl < al, then jump to update ( jb -> jump below )
mov   al  , bl                  ; Else if bl >= al, move current element in al i.e. update current largest num
update:
inc     rsi                     ; For each iteration, increment rsi (source array pointer)
dec     rcx                     ; Decrement loop counter
jnz     arrloop                 ; If loop counter is not equal to zero, jump to arrloop

mov     rcx   ,   02h
mov     rdi   ,   maxnumout
mov     bl    ,   al

hextoascii:
rol     bl    ,   04
mov     dl    ,   bl
and     dl    ,   0x0F
cmp     dl    ,   09h
jbe     copydigit
add     dl    ,   07h
copydigit:
add     dl     ,  30h 
mov     [rdi]  ,  dl
inc     rdi
dec     rcx
jnz     hextoascii

mov     byte[rdi]  ,  0xA

print   maxnumout  ,  03

exit