package assignment_05;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConnection {

    public static Connection initializeDatabase() throws SQLException {
        Connection connection = DriverManager.getConnection( 
            "jdbc:mysql://localhost:3306/wtl_05", 
            "root", 
            "root"
        ) ; 
        return connection ; 
    }

}
