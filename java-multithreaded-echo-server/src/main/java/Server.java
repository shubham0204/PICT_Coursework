import java.io.*;
import java.net.*;
import java.util.*;

public class Server {

    public static void main( String[] args ) {
        System.out.println( "Enter port address: " ) ;
        Scanner scanner = new Scanner( System.in ) ; 
        int port = scanner.nextInt() ; 
        scanner.close();
        try( ServerSocket socket = new ServerSocket( port ) ){
            while( true ) {
                Socket connectionSocket = socket.accept() ;
                System.out.println( "Server: Request received from => " + connectionSocket.getInetAddress().toString() ) ; 
                Thread newThread = new RequestHandler(connectionSocket) ; 
                newThread.start();
            }
        }
        catch( IOException e ) {
            e.printStackTrace();
        }
    }

}