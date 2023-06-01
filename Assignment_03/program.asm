; Shubham Panchal
; https://shubham0204.github.io

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

; Printing the array of numbers
mov   rcx  , 05h                     ; Counter for no. of digits to print
mov   r9   , 02h                     ; Counter for processing each digit two times

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
mov     [rdi]      ,  dl             ; Move converted digit in dl to location specified by rdi
inc     rdi                          ; Increment rdi (dest array pointer)
dec     r9                           ; Decrement r9
jnz     hextoascii1                  ; If r9 is not equal to 0, jump to hex2ascii1 
                                     ; (this will happen two times for each digit)
mov     r9         ,  02h            ; Reinitialize r9 to 02h
mov     byte[rdi]  ,  0xA            ; Add line break to show output on different lines
inc     rdi                          ; Increment rdi
inc     rsi                          ; Increment rsi
mov     bl         ,  [rsi]          ; Move next number in bl for conversion
dec     rcx                          ; Decrement array counter 
jnz     hextoascii1                  ; Jump if rcx is not zero

mov     byte[rdi]  ,  0xA       ; move 0xA (line break in ASCII) to rdi
print   arrout     ,  16        ; print arrout (with five more linebreaks, hence 16 bytes)

mov   rsi , arr                 ; Store source array pointer in rsi
mov   al  , 0h                  ; Stores the current largest number 
mov   rcx , 05h                 ; Counter for iterating through the array

; Iterate through `arr` to find the largest element
arrloop:
mov   bl  , [rsi]               ; Move element pointed by [rsi] to bl
cmp   bl  , al                  ; Compare current element (in bl) with al (current largest num)
jb    update                    ; If the bl < al, then jump to update ( jb -> jump below )
mov   al  , bl                  ; Else if bl >= al, move current element in al i.e. update current largest num
update:
inc     rsi                     ; For each iteration, increment rsi (source array pointer)
dec     rcx                     ; Decrement loop counter
jnz     arrloop                 ; If loop counter is not equal to zero, jump to arrloop

mov     rcx   ,   02h           ; Reset counter for displaying largest number (2 digits)
mov     rdi   ,   maxnumout     ; Set destination array to maxnumout (maximum number output)
mov     bl    ,   al            ; Move largest number (stored in al) to bl for hex2ascii conversion

; Conversion the hex val stored in al (the largest number) to ASCII for printing
hextoascii:
rol     bl    ,   04            ; Rotate bl four times (swap nibbles)
mov     dl    ,   bl            ; Move byte from bl to dl for conversion
and     dl    ,   0x0F          ; AND with 0x0F to make everything zero except for right-most nibble
cmp     dl    ,   09h           ; Compare dl with 0x09
jbe     copydigit               ; Jump to copydigit1 if cmp result was below or equal
add     dl    ,   07h           ; If there was no jump in above statement, add 07h to dl
copydigit:
add     dl     ,  30h           ; Add 30h always
mov     [rdi]  ,  dl            ; Move converted digit in dl to location specified by rdi
inc     rdi                     ; Increment rdi (dest array pointer)
dec     rcx                     ; Decrement counter rcx
jnz     hextoascii              ; If counter rcx is not equal to 0h, jump to hextoascii

mov     byte[rdi]  ,  0xA       ; move 0xA (line break in ASCII) to rdi
print   maxnumout  ,  03        ; print maxnumout with linebreak (hence 3 bytes)

exit