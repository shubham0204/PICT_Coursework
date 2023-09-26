from models import Blog
import mariadb

class Database:

    def __init__( self , host: str , port: int , db_name: str ):
        self.connection = mariadb.connect( 
            user="root" , 
            password="root" ,
            host=host , 
            port=port ,
            database=db_name
        ) 
        self.cursor = self.connection.cursor()

    def insert_blog( self , blog: Blog ) -> bool:
        self.cursor.execute( "insert into blogs( title , content ) values( '{}' , '{}' )".format( 
            blog.title , blog.content ))
        self.connection.commit()
        return self.cursor.affected_rows > 0
    
    def get_all_blogs( self ) -> list[Blog]:
        self.cursor.execute( "select * from blogs;" )
        blogs = []
        for (id, title, content) in self.cursor:
            blog = Blog()
            blog.id = id
            blog.title = title
            blog.content = content
            blogs.append( blog )
        return blogs
    
    def get_blog_from_id( self , id: int ) -> Blog:
        self.cursor.execute( "select * from blogs where id='{}';".format(id) )
        blogs = []
        for (id, title, content) in self.cursor:
           blog = Blog()
           blog.id = id
           blog.title = title
           blog.content = content
           blogs.append( blog )
        return blogs[0]
    
    def update_blog( self , new_blog: Blog ) -> bool:
        query = "update blogs set title='{}', content='{}' where id='{}';".format(
            new_blog.title, new_blog.content, new_blog.id)
        self.cursor.execute(query)
        self.connection.commit()
        return self.cursor.affected_rows > 0
    
    def delete_blog( self , id: int ) -> bool:
        query = "delete from blogs where id='{}';".format( id )
        self.cursor.execute(query)
        self.connection.commit()
        return self.cursor.affected_rows > 0
    
    def __del__( self ):
        self.connection.close()