package assignment_05;

import jakarta.servlet.http.HttpServlet;

import jakarta.servlet.http.*; 
import jakarta.servlet.*; 
import java.io.*;
import java.sql.Connection;
import java.sql.PreparedStatement;

public class InsertBook extends HttpServlet {

    @Override
    public void service(
        HttpServletRequest request ,
        HttpServletResponse response
    ) throws ServletException , IOException {
        try {
            Connection conn = DatabaseConnection.initializeDatabase() ; 
            String title = request.getParameter( "title" ) ; 
            String author = request.getParameter( "author" ) ;
            int price = Integer.parseInt( request.getParameter( "price" ) ) ; 
            int quantity = Integer.parseInt( request.getParameter( "quantity" ) ) ; 
            PreparedStatement statement = conn.prepareStatement( "insert into books( title , author , price , quantity ) values( ? , ? , ? , ? )" ) ; 
            statement.setString( 1 , title ) ; 
            statement.setString( 2 , author ) ; 
            statement.setInt( 3 , price ) ;
            statement.setInt( 4 , quantity ) ;
            statement.close() ; 
            conn.commit() ; 
            conn.close() ; 
        }
        catch( Exception e ) {
            e.printStackTrace();
        }
    }
    
}
