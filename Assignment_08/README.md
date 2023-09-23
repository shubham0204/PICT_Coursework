# Connecting MariaDB with JDBC

### Build Instructions

```
$ javac src/main/java/database/BlogsTable.java \ src/main/java/models/Blogs.java src/main/java/Main.java -d build
$ java -classpath "build;src/main/resources/mysql-connector-j-8.1.0.jar;." Main
```