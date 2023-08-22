
#include "assembler_pass_2.cpp"

int main(int argc, char *argv[]) {
    std::cout << "----------- Test case 1 ------------------ \n\n\n" ; 
    AssemblerPass1 assembler1( "../testcase_01.txt" ) ;
    assembler1.performPass() ; 
    std::cout << "\n\n\n" ;

    std::cout << "----------- Test case 2 ------------------ \n\n\n" ; 
    AssemblerPass1 assembler2( "../testcase_02.txt" ) ;
    assembler2.performPass() ; 
    std::cout << "\n\n\n" ;

    std::cout << "----------- Test case 3 ------------------ \n\n\n" ; 
    AssemblerPass1 assembler3( "../testcase_03.txt" ) ;
    assembler3.performPass() ; 
    std::cout << "\n\n\n" ;

    AssemblerPass2 pass2 ; 
    pass2.performPass() ; 

    return 0;
}