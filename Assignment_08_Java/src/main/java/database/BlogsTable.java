package database;

import java.sql.Connection; 
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;

public class BlogsTable {

    private Connection databaseConnection ; 
    private String databaseUrl = "jdbc:mariadb://localhost:3306/assignment_08" ; 
    private String databaseUser = "root" ; 
    private String databasePassword = "root" ; 

    public BlogsTable() {
        try {
            databaseConnection = DriverManager.getConnection(
                databaseUrl , 
                databaseUser,
                databasePassword ) ; 
            Statement statement = databaseConnection.createStatement() ; 
            ResultSet results = statement.executeQuery( "show tables" ) ; 
            while( results.next() ) {
                String name = results.getString( "Tables_in_assignment_08" ) ; 
                System.out.println( name ) ; 
            }
            databaseConnection.close();
        }
        // catch( ClassNotFoundException e ) {
           // e.printStackTrace();
        // }
        catch( SQLException e ) {
            e.printStackTrace();
        }
        
    }



}
