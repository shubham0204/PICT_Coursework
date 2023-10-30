import database.Database;
import models.Blog;

import java.util.*;

public class Main {

    public static void main( String[] args ) {
        Database db = new Database() ; 
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
                db.insertBlog( blog );
                System.out.println( "Inserted successfully!" ) ; 
            }
            else if( option == 2 ) {
                List<Blog> blogs = db.getAllBlogs() ; 
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
                if( db.updateBlog( blog ) ) {
                    System.out.println( "Updated successfully!" ) ; 
                }
                else {
                    System.out.println( "Updation failed" ) ; 
                }
            }

                 /* 
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
            */
        }
        scanner.close() ; 
        // table.close();
    }

}