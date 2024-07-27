#include <stdlib.h>
#include <stdio.h>

#define PRINT_INT(n) (printf("%d\n",n))
#define PRINTLN(s) (printf("%s\n",s))
#define SCAN_INT(n) (scanf("%d",&n))

int _fibonacci_recur(
    int i
) {
    if (i == 0 || i == 1) return i;
    return _fibonacci_recur(i - 1) + _fibonacci_recur(i - 2) ;
}

int fibonacci_recur(
    int n
) {
    for (int i = 0; i < n; i++) {
        int f_i = _fibonacci_recur(i) ;
        PRINT_INT(f_i) ;
    }
}

void fibonacci_iter(
    int n
) {
    int f_0 = 0 ;
    int f_1 = 1 ;
    PRINT_INT(f_0) ;
    PRINT_INT(f_1) ;
    for (int i = 0; i < n - 2; i++) {
        int f_2 = f_0 + f_1 ; 
        PRINT_INT(f_2) ;
        f_0 = f_1 ;
        f_1 = f_2 ;
    }
}

int main(
    int argc , 
    char** argv
) {
    while (1) {
        PRINTLN( "Enter the value of 'n':" ) ;
        int n = 0 ;
        SCAN_INT( n ) ;
        PRINTLN( "Choose option:" ) ;
        PRINTLN( "0: Recursive" ) ;
        PRINTLN( "1: Iterative" ) ;
        PRINTLN( "2: Close" ) ;
        int opt = 2 ;
        SCAN_INT( opt ) ;
        switch (opt) {
            case 0:
                fibonacci_recur(n) ;
                break;
            case 1:
                fibonacci_iter(n) ;
                break;
            case 2:
                exit(0) ;
                break;        
        }
    }
}