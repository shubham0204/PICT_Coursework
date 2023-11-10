import java.net.*;
import java.io.*;
import java.util.*;

public class Client {

    public static void main( String[] args ) {
        try( Scanner scanner = new Scanner( System.in ) ) {
            System.out.println( "Enter port address: " ) ;
            int port = scanner.nextInt() ; 
            scanner.nextLine() ; 
            while( true ) {
                System.out.println( "Enter message: " ) ; 
                String message = scanner.nextLine() ; 
                Socket connectionSocket = new Socket( "localhost" , port ) ; 
                PrintWriter out = new PrintWriter( connectionSocket.getOutputStream() , true ) ; 
                BufferedReader in = new BufferedReader( new InputStreamReader( connectionSocket.getInputStream() ) )  ;
                out.println( message ) ; 
                String response = in.readLine() ; 
                System.out.println( "Client: Received response: " + response ) ;
                in.close();
                out.close();
                connectionSocket.close();
            }
        }
        catch( IOException e ) {
            e.printStackTrace();
        }
    }
    
}
