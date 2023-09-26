#include "macro_processor_pass_1.cpp"

int main( int argc , char** argv ) {
    MacroProcessor macroProcessor( "testcase_02.txt" ) ;
    MacroProcessor.perform() ; 
    return 0;
}