
import java.util.*;
import database.BlogsTable;
import models.Blog;

public class Main {

    public static void main( String[] args ) {
        BlogsTable table = new BlogsTable() ; 
        Scanner scanner = new Scanner( System.in ) ; 
        while( true ) {
            System.out.println( "Options are \n1 => Insert blog\n2 => Get All Blogs\n3 => Update Blog\n4 => Delete Blog" );
            int option = scanner.nextInt() ; 
            if ( option == 0 ) {
                break ; 
            }
            scanner.nextLine() ; 
            if( option == 1  ) { 
                System.out.println( "Enter title: " ) ; 
                String title = scanner.nextLine() ; 
                System.out.println( "Enter content: " ) ; 
                String content = scanner.nextLine() ; 
                Blog blog = new Blog() ; 
                blog.title = title ; 
                blog.content = content ; 
                if( table.insertBlog( blog ) ) {
                    System.out.println( "Inserted successfully!" ) ; 
                }
                else {
                    System.out.println( "Insertion failed" ) ; 
                }
            }
            else if( option == 2 ) {
                List<Blog> blogs = table.getAllBlogs() ; 
                for( Blog blog : blogs ) {
                    System.out.println( "--------------" ) ; 
                    System.out.println( "id: " + blog.id ) ; 
                    System.out.println( "title: " + blog.title ) ; 
                    System.out.println( "content: " + blog.content ) ; 
                }
            }
            else if( option == 3 ) {
                System.out.println( "Enter id: " ) ; 
                int id = scanner.nextInt() ; 
                scanner.nextLine() ; 
                System.out.println( "Enter new title: " ) ; 
                String title = scanner.nextLine() ; 
                System.out.println( "Enter new content: " ) ; 
                String content = scanner.nextLine() ; 
                Blog blog = new Blog() ; 
                blog.id = id ; 
                blog.title = title ; 
                blog.content = content ; 
                if( table.updateBlog( blog ) ) {
                    System.out.println( "Updated successfully!" ) ; 
                }
                else {
                    System.out.println( "Updation failed" ) ; 
                }
            }
            else {
                System.out.println( "Enter blog id: " ) ; 
                int id = scanner.nextInt() ;
                scanner.nextLine() ; 
                if( table.deleteBlog( id ) ) {
                    System.out.println( "deleted successfully!" ) ; 
                }
                else {
                    System.out.println( "Deletion failed" ) ; 
                }
            }
        }
        scanner.close() ; 
        table.close();
    }
    
}
