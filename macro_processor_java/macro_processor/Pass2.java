package macro_processor;

import java.io.* ; 

public class Pass2 {

    
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
