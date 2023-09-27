package database;

import java.sql.*;
import java.util.*;
import models.Blog;

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
        }
        catch( SQLException e ) {
            e.printStackTrace();
        }
    }

    public boolean insertBlog( Blog blog ) {
        try {
            Statement statement = databaseConnection.createStatement() ; 
            String query = "insert into blogs( title , content ) values( 'TITLE' , 'CONTENT' ) ;"
                .replace( "TITLE" , blog.title )
                .replace( "CONTENT" , blog.content ) ; 
            int affectedRows = statement.executeUpdate( query ) ; 
            return affectedRows > 0 ; 
        }
        catch( SQLException e ) {
            e.printStackTrace();
            return false ; 
        }
    }

    public List<Blog> getAllBlogs() {
        try {
            Statement statement = databaseConnection.createStatement() ; 
            String query = "select * from blogs;" ; 
            ResultSet results = statement.executeQuery( query ) ; 
            ArrayList<Blog> blogs = new ArrayList<>() ; 
            while( results.next() ) {
                Blog blog = new Blog() ; 
                blog.id = results.getInt( "id" ) ;
                blog.title = results.getString( "title" ) ; 
                blog.content = results.getString( "content" ) ; 
                blogs.add( blog ) ; 
            }
            return blogs; 
        }
        catch( SQLException e ) {
            e.printStackTrace();
            return new ArrayList<Blog>() ; 
        }
    }

    public boolean updateBlog( Blog newBlog ) {
        try {
            Statement statement = databaseConnection.createStatement() ; 
            String query = "update blogs set title='TITLE', content='CONTENT' where id='ID'"
                .replace( "TITLE" , newBlog.title ) 
                .replace( "CONTENT" , newBlog.content ) 
                .replace( "ID" , String.valueOf( newBlog.id ) ) ; 
            int affectedRows = statement.executeUpdate( query ) ; 
            return affectedRows > 0 ; 
        }
        catch( SQLException e ) {
            e.printStackTrace();
            return false ;
        }
    }

    public boolean deleteBlog( int id ) {
        try {
            Statement statement = databaseConnection.createStatement() ; 
            String query = "delete from blogs where id='ID'"
                .replace( "ID" , String.valueOf( id ) ) ; 
            int affectedRows = statement.executeUpdate( query ) ; 
            return affectedRows > 0 ; 
        }
        catch( SQLException e ) {
            e.printStackTrace();
            return false ;
        }
    }

    public void close() {
        try {
            databaseConnection.close();
        }
        catch( SQLException e ) {
            e.printStackTrace();
        }
    }


}
