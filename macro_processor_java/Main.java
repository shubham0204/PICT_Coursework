import macro_processor.*;

public class Main {

    public static void main( String[] args ) {
        Pass1 pass1 = new Pass1( "testcase_01.txt" ) ; 
        pass1.perform();
        Pass2 pass2 = new Pass2( "mntab.dat", "kpdtab.dat", "pntab.dat", "mdtab.dat" ) ; 
        
    }

}
