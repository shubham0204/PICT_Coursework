-- Grant permissions
GRANT ALL PRIVILEGES ON my_database.* TO 'username'@'localhost';
GRANT SELECT, INSERT ON my_database.my_table TO 'username'@'localhost';
GRANT ALL PRIVILEGES ON *.* TO 'username'@'localhost';

-- Revoke permissions
REVOKE ALL PRIVILEGES ON my_database.* FROM 'username'@'localhost';
REVOKE SELECT, INSERT ON my_database.my_table FROM 'username'@'localhost';
REVOKE ALL PRIVILEGES ON *.* FROM 'username'@'localhost';

-- Apply changes on permissions
FLUSH PRIVILEGES;