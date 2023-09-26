from database import Database
from models import Blog

"""
Make sure a database "assignment_08" is created with 
table `blogs`
"""
db = Database( "localhost" , 3306 , "assignment_08" )

print( 
    """
    Blogs database: Options
    1. Insert blog
    2. Read all blogs
    3. Read blog from id
    4. Update blog
    5. Delete blog
    """
)

while True:

    option = int( input( "Enter option: " ) )
    if option == 1:
        title = input( "Enter title: " )
        content = input( "Enter content: " )
        blog = Blog() 
        blog.title = title
        blog.content = content
        if db.insert_blog( blog ):
            print( "Inserted blog!" )
    elif option == 2:
        blogs = db.get_all_blogs()
        for blog in blogs:
            print( blog.id )
            print( blog.title )
            print( blog.content )
            print( "--------------" )
    elif option == 3:
        id = int( input( "Enter blog id: " ) )
        blog = db.get_blog_from_id( id )
        print( blog.id )
        print( blog.title )
        print( blog.content )
    elif option == 4:
        id = int( input( "Enter blog id: " ) )
        title = input( "Enter new title: " )
        content = input( "Enter new content: " )
        blog = Blog() 
        blog.id = id
        blog.title = title
        blog.content = content
        if db.update_blog( blog ):
            print( "Updated blog!" )
    elif option == 5:
        id = int( input( "Enter blog id: " ) )
        if db.delete_blog( id ):
            print( "Deleted blog!" )   
    
