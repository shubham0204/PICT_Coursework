package assignment_05;

import java.io.PrintWriter;
import jakarta.servlet.http.*; 
import jakarta.servlet.*; 
import java.io.*; 

public class AddServlet extends HttpServlet {

    @Override
    public void service(
        HttpServletRequest request ,
        HttpServletResponse response
    ) throws ServletException , IOException {
        int a = Integer.parseInt( request.getParameter( "num1" ) ) ;
        int b = Integer.parseInt( request.getParameter( "num2" ) ) ;

        PrintWriter writer = response.getWriter() ; 
        writer.println( "Sum: " + String.valueOf( a + b ) ) ;
        writer.close() ; 
    }

} 
