<html>
    <head>
        <title>JDBC Connectivity with JSP</title>
    </head>
    <% 
        java.sql.Connection connection = java.sql.DriverManager.getConnection( "jdbc:mariadb://localhost:3306/students_db" , "root" , "root" ) ; 
        java.sql.ResultSet results = connection.createStatement().executeQuery( "select * from students" ) ; 
    %>
     <table>
        <tr>
           <th>Student ID</th>
           <th>Name</th>
           <th>Class</th>
           <th>Division</th>
           <th>City</th>
        </tr>
        <% while( results.next() ) { %>
            <tr>
                <td><%= results.getInt( "stud_id" )%></td>
                <td><%= results.getString( "stud_name" )%></td>
                <td><%= results.getInt( "class" )%></td>
                <td><%= results.getString( "division" )%></td>
                <td><%= results.getString( "city" )%></td>
            </tr>
        <% } %>
        <% connection.close() ; %>
     </table>
    </body>
</html>