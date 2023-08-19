#include "assembler.cpp"

int main(int argc, char *argv[]) {
    std::cout << "----------- Test case 1 ------------------ \n\n\n" ; 
    Assembler assembler1( "../testcase_01.txt" ) ;
    assembler1.performPass1() ; 
    std::cout << "\n\n\n" ;

    std::cout << "----------- Test case 2 ------------------ \n\n\n" ; 
    Assembler assembler2( "../testcase_02.txt" ) ;
    assembler2.performPass1() ; 
    std::cout << "\n\n\n" ;

    std::cout << "----------- Test case 3 ------------------ \n\n\n" ; 
    Assembler assembler3( "../testcase_03.txt" ) ;
    assembler3.performPass1() ; 
    std::cout << "\n\n\n" ;
    return 0;
}