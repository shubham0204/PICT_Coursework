package database;

import java.sql.*;
import java.util.*;
import database.Blog;


public class BlogsTable {
	
	private Connection dbConnection ; 
	private String dbHost = "jdbc:mariadb://localhost:3306/assignment_08" ; 
	private String dbUser = "root" ;
	private String dbPassword = "root" ; 
	
	public BlogsTable() {
		try {
			dbConnection = DriverManager.getConnection(dbHost , dbUser , dbPassword) ;
		}
		catch( SQLException e ) {
			e.printStackTrace();
		}
	}
	
	public boolean insertBlog( Blog blog ) {
		try {
			String query = "insert into blogs( title , content ) values ( ? , ? )" ; 
			PreparedStatement ps = dbConnection.prepareStatement( query ) ; 
			ps.setString( 1 , blog.getTitle() );
			ps.setString( 2 , blog.getContent() );
			int affectedRows = ps.executeUpdate() ; 
			dbConnection.commit();
			return affectedRows > 0;
		}
		catch( SQLException e ) {
			e.printStackTrace();
			return false;
		}
	}
	
	public List<Blog> getAllBlogs() {
		try {
			String query = "select * from blogs" ;
			Statement s = dbConnection.createStatement() ; 
			ResultSet results = s.executeQuery(query) ; 
			ArrayList<Blog> blogs = new ArrayList<Blog>() ; 
			while( results.next() ) {
				int id = results.getInt( "id" ) ; 
				String title = results.getString( "title" ) ; 
				String content = results.getString( "content" ) ;
				blogs.add( new Blog( id , title , content ) ) ;
			}
			return blogs;
		}
		catch( SQLException e ) {
			e.printStackTrace();
			return new ArrayList<Blog>() ; 
		}
	}
	
	public int updateBlog( Blog newBlog ) {
		try {
			String query = "update blogs set title = ?, content = ? where id = ?" ; 
			PreparedStatement ps = dbConnection.prepareStatement( query ) ; 
			ps.setString( 1 , newBlog.getTitle() );
			ps.setString( 2 , newBlog.getContent() );
			ps.setInt( 3 , newBlog.getId() );
			int affectedRows = ps.executeUpdate() ; 
			dbConnection.commit();
			return affectedRows;
		}
		catch( SQLException e ) {
			e.printStackTrace();
			return 0;
		}
	}
	
	public int deleteBlog( int id ) {
		try {
			String query = "delete from blogs where id = ?" ;
			PreparedStatement ps = dbConnection.prepareStatement( query ) ; 
			ps.setInt( 1 , id ) ;
			int affectedRows = ps.executeUpdate() ; 
			dbConnection.commit();
			return affectedRows ; 
		}
		catch( SQLException e ) {
			e.printStackTrace();
			return 0;
		}
	}
	
	public void close() {
		try {
			dbConnection.close(); 
		}
		catch( SQLException e ) {
			e.printStackTrace();
		}
	}

}
