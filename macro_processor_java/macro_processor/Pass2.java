package macro_processor;

import java.io.* ;
import java.util.*;

import javax.swing.Painter; 

public class Pass2 {

    class MNTabEntry implements Serializable {

        public String macroName ; 
        public int numKPD = 0 ;
        public int numPP = 0 ;
        public int mdtabPtr = 0;
        public int kpdtabPtr = 0;

        public MNTabEntry() {
        }
        
        public MNTabEntry( String macroName , int numKPD , int numPP , int mdtabPtr , int kpdtabPtr ) {
            this.macroName = macroName ; 
            this.numKPD = numKPD ; 
            this.numPP = numPP ; 
            this.mdtabPtr = mdtabPtr ; 
            this.kpdtabPtr = kpdtabPtr ; 
        }

    }

    class MDTabEntry implements Serializable {

        public String mnemonic ; 
        public String operand1 ; 
        public String operand2 ; 
        public int operand1Index = -1; 
        public int operand2Index = -1; 
    
    }

    private HashMap<String,List<String>> pntabMap ; 
    private ArrayList<String[]> kpdtab ; 
    private ArrayList<MNTabEntry> mntab ; 
    private ArrayList<MDTabEntry> mdtab ; 
    private ArrayList<String[]> aptab ; 

    public Pass2( String mntabFilepath , String kpdtabFilepath , String pntabMapFilepath , String mdtabFilepath ) {
        mntab = (ArrayList<MNTabEntry>) loadTable(mdtabFilepath) ; 
        kpdtab = (ArrayList<String[]>) loadTable(kpdtabFilepath) ; 
        pntabMap = (HashMap<String,List<String>>) loadTable(pntabMapFilepath) ; 
        mdtab = (ArrayList<MDTabEntry>) loadTable(mdtabFilepath) ; 
    }

    public void processCall( String call ) {
        String macroName = call.split( "(" )[0] ; 
        List<String> pntab = pntabMap.get( macroName ) ; 
        String[] actualParams = call.split( "(" )[1].split( ")" )[0].split( "," ) ;
        for( int i = 0 ; i < actualParams.length ; i++ ) {
            if( actualParams[i].contains( "=" ) )  {
                // Handle default parameter
                
            } 
            else {
                // Positional parameter

            }
        }
    } 
    
    private static Object loadTable( String filepath ) {
        try {
            FileInputStream fin = new FileInputStream( new File( filepath ) ) ; 
            ObjectInputStream inputStream = new ObjectInputStream(fin) ; 
            Object table = inputStream.readObject() ; 
            inputStream.close();
            fin.close();
            return table ;
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
