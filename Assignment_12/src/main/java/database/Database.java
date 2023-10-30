package database;

import models.Blog;
import com.mongodb.client.*;
import com.mongodb.*;
import models.Blog;
import java.util.*;

import javax.swing.text.Document;

import org.bson.*;
import org.bson.types.*;
import java.io.*;  

public class Database {

    private String CONNECTION_URL = "mongodb+srv://admin:<password>@cluster0.qhdzsex.mongodb.net/?retryWrites=true&w=majority" ; 
    private MongoClient client ;
    private MongoDatabase database ;
    private MongoCollection<Document> collection ; 

    public Database() {
        this.CONNECTION_URL = this.CONNECTION_URL.replace( "<password>" , readPassword() ) ;
        System.out.println( this.CONNECTION_URL ) ; 
        this.client = MongoClients.create( CONNECTION_URL ) ; 
        this.database = client.getDatabase( "test-atlas-database" ) ;
        this.collection = this.database.getCollection( "test-collection" ) ; 
        // getAllBlogs() ; 

    }

    private String readPassword() {
        try {
            BufferedReader reader = new BufferedReader( new FileReader( "src/main/resources/password.txt" ) ) ;
            String password = reader.readLine().trim() ; 
            reader.close() ; 
            return password ;
        }
        catch( IOException e ) {
            e.printStackTrace();
            return "" ; 
        }
    }

    public void insertBlog( Blog blog ) {
        Document doc = new Document("_id", new ObjectId() );
        doc.append( "title" , blog.title ) ;
        doc.append( "content" , blog.content ) ; 
        this.collection.insertOne( doc ) ; 
    }

    public List<Blog> getAllBlogs() {
        MongoCursor cursor = this.collection.find().cursor();
        List<Blog> blogs = new ArrayList<>() ; 
        while (cursor.hasNext()) {
            Document obj = (Document) cursor.next();
            Blog blog = new Blog() ; 
            blog.id = obj.getInteger( "_id" ).toString() ; 
            blog.title = obj.getString( "title" ) ;
            blog.content = obj.getString( "content" ) ; 
            blogs.add( blog ) ;
        }
        return blogs;
    }

    public void updateBlog( Blog newBlog ) {
        Document doc = new Document("_id", new ObjectId() );
        doc.append( "title" , newBlog.title ) ;
        doc.append( "content" , newBlog.content ) ; 
        this.collection.updateOne( Filters.eq("color", "pink"); , doc ) ; 
    }


}