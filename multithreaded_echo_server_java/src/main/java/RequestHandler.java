import java.io.*;
import java.net.*;

public class RequestHandler extends Thread {

    private Socket connectionSocket ; 
    private PrintWriter out ; 
    private BufferedReader in ; 

    public RequestHandler( Socket connectionSocket )  {
        try {
            this.connectionSocket = connectionSocket ; 
            this.out = new PrintWriter( connectionSocket.getOutputStream() , true ) ; 
            this.in = new BufferedReader( new InputStreamReader( connectionSocket.getInputStream() ) ) ;
        }
        catch( IOException e ) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        try {
            String message = in.readLine() ; 
            System.out.println( "Server: Received message => " + message ) ;
            out.println( message );
            System.out.println( "Server: Message sent => " + message ) ;
            out.close();
            in.close();
            connectionSocket.close();
        }
        catch( IOException e ) {
            e.printStackTrace() ;
        }
    }

}
