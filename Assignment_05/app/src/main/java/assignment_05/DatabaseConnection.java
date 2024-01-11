package assignment_05;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConnection {

    public static Connection initializeDatabase() throws SQLException , ClassNotFoundException {
        Class.forName("org.mariadb.jdbc.Driver");
        Connection connection = DriverManager.getConnection( 
            "jdbc:mariadb://localhost:3306/wtl_05", 
            "root", 
            "root"
        ) ; 
        return connection ; 
    }

}
