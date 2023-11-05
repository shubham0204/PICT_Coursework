import database.BlogsTable;
import database.Blog;
import java.util.*;

public class Main {
	
	public static void main( String[] args ) {
		BlogsTable table = new BlogsTable() ;
		Scanner s = new Scanner( System.in ) ; 
		while( true ) {
			System.out.println( "1. Insert blog" ) ;
			System.out.println( "2. Read all blogs" ) ;
			System.out.println( "3. Update blog" ) ;
			System.out.println( "4. Delete blog" ) ;
			System.out.println( "Enter option: " ) ;
			
			int option = s.nextInt() ;
			s.nextLine(); 
			
			if( option == 1 ) {
				System.out.println( "Enter title: " ) ; 
				String title = s.nextLine() ; 
				System.out.println( "Enter content: " ) ; 
				String content = s.nextLine() ; 
				table.insertBlog( new Blog( title , content ) ) ; 
			}
			else if( option == 2 ) {
				List<Blog> blogs = table.getAllBlogs() ; 
				for( Blog blog : blogs ) {
					System.out.println( blog.getId() ) ; 
					System.out.println( blog.getTitle() ) ; 
					System.out.println( blog.getContent() ) ; 
					System.out.println( "---------------" ) ;
				}
			}
			else if( option == 3 ) {
				System.out.println( "Enter title: " ) ; 
				String title = s.nextLine() ; 
				System.out.println( "Enter content: " ) ; 
				String content = s.nextLine() ; 
				table.insertBlog( new Blog( title , content ) ) ; 
			}
			else if( option == 4 ) {
				System.out.println( "Enter id: " ) ; 
				int id = s.nextInt() ; 
				table.deleteBlog( id ) ;
			}
			else {
				break;
			}
		}			
		table.close() ; 
 	}
	
	
}
