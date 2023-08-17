#include "assembler.cpp"

int main() {
    Assembler assembler( "../testcase_02.txt" ) ;
    assembler.performPass1() ; 
    return 0;
}