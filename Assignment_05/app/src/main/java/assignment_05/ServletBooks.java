package assignment_05;

import jakarta.servlet.http.*; 
import jakarta.servlet.*; 
import java.io.*;
import java.sql.*;
import java.util.ArrayList;

import com.google.gson.Gson;

public class ServletBooks extends HttpServlet {

    @Override
    public void doPost(
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
            statement.execute() ; 
            conn.commit() ; 
            conn.close() ; 
            response.setStatus( 201 );
        }
        catch( Exception e ) {
            e.printStackTrace();
            response.sendError( 500 , e.getMessage() );
        }
    }

    public void doGet(
        HttpServletRequest request ,
        HttpServletResponse response
    ) throws ServletException , IOException {
        try {
            Connection conn = DatabaseConnection.initializeDatabase() ; 
            Statement statement = conn.createStatement() ; 
            ResultSet results = statement.executeQuery( "select * from books" ) ; 
            ArrayList<Book> books = new ArrayList<Book>() ; 
            while( results.next() ) {
                Book book = new Book( 
                    results.getInt( "id" ) , 
                    results.getString( "title" ) ,
                    results.getString( "author" ) , 
                    results.getInt( "price" ) , 
                    results.getInt( "quantity" ) 
                ) ;  
                books.add( book ) ; 
            }
            String booksJson = new Gson().toJson( books ) ; 
            PrintWriter out = response.getWriter();
            response.setContentType("application/json");
            response.setCharacterEncoding("UTF-8");
            out.print( booksJson );
            out.flush();
        }
        catch( Exception e ) {
            e.printStackTrace();
            response.sendError( 500 , e.getMessage() );
        }
    }
    
}
