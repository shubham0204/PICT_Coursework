#include "macro_processor_pass_1.cpp"

int main( int argc , char** argv ) {
    Pass1 pass1( "testcase_01.txt" ) ;
    pass1.perform() ; 
    return 0;
}