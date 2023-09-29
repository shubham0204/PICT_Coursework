
#include "assembler_pass_2.cpp"

int main(int argc, char *argv[]) {

    std::cout << "----------- Test case 1 ------------------ \n\n\n" ; 
    AssemblerPass1 pass11( "../testcase_01.txt" , "ic_01.txt" , "stab_01.dat" , "lttab_01.dat" ) ;
    pass11.performPass() ; 
    std::cout << "\n\n\n" ;
    std::cout << "----------- Test case 2 ------------------ \n\n\n" ; 
    AssemblerPass1 pass12( "../testcase_02.txt" , "ic_02.txt" , "stab_02.dat" , "lttab_02.dat" ) ;
    pass12.performPass() ; 
    std::cout << "\n\n\n" ;
    std::cout << "----------- Test case 3 ------------------ \n\n\n" ; 
    AssemblerPass1 pass13( "../testcase_03.txt" , "ic_03.txt" , "stab_03.dat" , "lttab_03.dat" ) ;
    pass13.performPass() ; 
    std::cout << "\n\n\n" ;
    std::cout << "----------- Pass 2 Output ------------------ \n\n\n" ; 
    std::cout << "----------- Test case 1 ------------------ \n\n\n" ; 
    AssemblerPass2 pass21( "ic_01.txt" , "stab_01.dat" , "lttab_01.dat" ); 
    pass21.performPass() ; 
    std::cout << "----------- Test case 2 ------------------ \n\n\n" ; 
    AssemblerPass2 pass22( "ic_02.txt" , "stab_02.dat" , "lttab_02.dat" ); 
    pass22.performPass() ; 
    std::cout << "----------- Test case 3 ------------------ \n\n\n" ; 
    AssemblerPass2 pass23( "ic_03.txt" , "stab_03.dat" , "lttab_03.dat" ); 
    pass23.performPass() ;


    return 0;
}