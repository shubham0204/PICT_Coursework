global   proc_count_char
global   proc_count_lines
global   proc_count_spaces

extern   filesize
extern   buffer
extern   input_char
extern   count_char
extern   count_lines
extern   count_spaces


proc_count_char:
mov         rcx          ,   [filesize]
mov         rsi          ,   buffer
br01:
mov         bl           ,   [input_char]
loop3:
mov         al           ,   byte[rsi]
cmp         al           ,   bl
jne         cont_loop3
inc         byte[count_char]
cont_loop3:
inc         rsi
dec         rcx
jnz         loop3
ret



proc_count_lines:
mov         rcx          ,   [filesize]
mov         rsi          ,   buffer
loop2:
mov         al           ,   byte[rsi]
cmp         al           ,   0Ah
jne         cont_loop2
inc         byte[count_lines]
cont_loop2:
inc         rsi
dec         rcx
jnz         loop2
add         byte[count_lines] , 01h
ret



proc_count_spaces:
mov         rcx          ,   [filesize]
mov         rsi          ,   buffer
loop1:
mov         al           ,   byte[rsi]
cmp         al           ,   20h
jne         cont_loop1
inc         byte[count_spaces]
cont_loop1:
inc         rsi
dec         rcx
jnz         loop1
add         byte[count_spaces] , 01h
ret