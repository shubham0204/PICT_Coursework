package mongodb_connectivity;

import org.bson.Document;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;

import java.util.*;

public class Main {
	
	public static void main( String[] args ) {
		MongoClient client = MongoClients.create( "mongodb://localhost:27017" ) ; 
		MongoDatabase db = client.getDatabase( "assignment_12" ) ;
		MongoCollection<Document> collection = db.getCollection( "blogs" ) ;
		
		Scanner scanner = new Scanner( System.in ) ;
		
		while( true ) {
			System.out.println( "1. Insert blog" ) ;
			System.out.println( "2. Get all blogs" ) ;
			System.out.println( "3. Update blog" ) ;
			System.out.println( "4. Delete blog" ) ;
			
			
			int option = scanner.nextInt() ;
			scanner.nextLine() ; 
			
			if( option == 1 ) {
				Document newDoc = new Document();  
				
				System.out.println( "Enter title: " ) ;
				String title = scanner.nextLine() ; 
				System.out.println( "Enter content: " ) ;
				String content = scanner.nextLine() ; 
				
				newDoc.append( "_id" , UUID.randomUUID().toString() ) ; 
				newDoc.append( "title" , title ) ;
				newDoc.append( "content" , content) ; 
				
				collection.insertOne( newDoc ) ;  
			}
			else if ( option == 2 ) {
				MongoCursor<Document> docs = collection.find().cursor() ;
				while( docs.hasNext() ) {
					Document blog = docs.next() ; 
					String id = blog.getString( "_id" ) ;
					String title = blog.getString( "title" ) ; 
					String content = blog.getString( "content" ) ;
					System.out.println( id + "\n" + title + "\n" + content ) ;
					System.out.println( "---------------------------------" ) ;
				}
			}
			else if( option == 3 ) {
				Document newDoc = new Document();  
				
				System.out.println( "Enter id: " ) ;
				String id = scanner.nextLine() ; 
				System.out.println( "Enter new title: " ) ;
				String title = scanner.nextLine() ; 
				System.out.println( "Enter new content: " ) ;
				String content = scanner.nextLine() ; 
				
				newDoc.append( "_id", id ) ; 
				newDoc.append( "title" , title ) ;
				newDoc.append( "content" , content) ; 
				
				collection.updateOne( 
						Filters.eq( "_id" , id ) ,
						Updates.combine( 
									Updates.set( "title" , title ) , 
									Updates.set( "content" , content )
								)
				) ;
			}
			else if( option == 4 ) {
				System.out.println( "Enter id: " ) ;
				String id = scanner.nextLine() ; 
				collection.deleteOne( Filters.eq( "_id" , id ) ) ;
			}
			else {
				break;
			}
			
		}

		scanner.close() ; 
		client.close() ;
	}

}
