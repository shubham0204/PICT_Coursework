package macro_processor;

import java.io.* ;
import java.util.*;
import macro_processor.Pass1.MDTabEntry;
import macro_processor.Pass1.MNTabEntry;

public class Pass2 {

    private HashMap<String,List<String>> pntabMap ; 
    private ArrayList<String[]> kpdtab ; 
    private ArrayList<MNTabEntry> mntab ; 
    private ArrayList<MDTabEntry> mdtab ; 
    private ArrayList<String[]> aptab = new ArrayList<>(); 

    public Pass2( String mntabFilepath , String kpdtabFilepath , String pntabMapFilepath , String mdtabFilepath ) {
        mntab = (ArrayList<MNTabEntry>) loadTable(mntabFilepath) ; 
        kpdtab = (ArrayList<String[]>) loadTable(kpdtabFilepath) ; 
        pntabMap = (HashMap<String,List<String>>) loadTable(pntabMapFilepath) ; 
        mdtab = (ArrayList<MDTabEntry>) loadTable(mdtabFilepath) ; 
    }

    public void processCall( String call ) {
        String macroName = call.split( "[(]" )[0] ; 
        List<String> pntab = pntabMap.get( macroName ) ; 
        String[] actualParams = call.split( "[(]" )[1].split( "[)]" )[0].split( "[,]" ) ;
        for( int i = 0 ; i < actualParams.length ; i++ ) {
            if( actualParams[i].contains( "=" ) )  {
                // Handle default parameter
                aptab.add( new String[]{ pntab.get(i) , actualParams[i].split("[=]")[1] } ) ;
            } 
            else {
                // Positional parameter
                aptab.add( new String[]{ pntab.get(i) , actualParams[i] } ) ;
            }
        }

        int mdtabPtr = 0 ;
        for( MNTabEntry entry : mntab ) {
            if( entry.macroName == macroName ) {
                mdtabPtr = entry.mdtabPtr ; 
                break ; 
            }
        }

        MDTabEntry currentEntry = mdtab.get(mdtabPtr) ; 
        while( !currentEntry.mnemonic.equals( "MEND" ) ) {

            String op1 = "" ; 
            if( currentEntry.operand1Index != -1 ) {
                op1 = aptab.get( currentEntry.operand1Index )[1]; 
            }
            else {
                op1 = currentEntry.operand1 ; 
            }

            String op2 = "" ; 
            if( currentEntry.operand2Index != -1 ) {
                op2 = aptab.get( currentEntry.operand2Index )[1]; 
            }
            else {
                op2 = currentEntry.operand2 ; 
            }

            System.out.println( currentEntry.mnemonic + " " + op1 + " " + op2 ) ;  
            mdtabPtr++ ; 
            currentEntry = mdtab.get( mdtabPtr ) ; 
        }
    } 
    
    private static Object loadTable( String filepath ) {
        try {
            FileInputStream fin = new FileInputStream( new File( filepath ) ) ; 
            ObjectInputStream inputStream = new ObjectInputStream(fin) ; 
            Object table = inputStream.readObject() ; 
            inputStream.close();
            fin.close();
            return table;
        }
        catch( ClassNotFoundException e ){
            e.printStackTrace();
        }
        catch( FileNotFoundException e ){
            e.printStackTrace();
        }
        catch( IOException e ) {
            e.printStackTrace(); 
        }
        return null ; 
    }
    
}
