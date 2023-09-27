# Connecting MariaDB with JDBC

### Build Instructions

```
$ javac src/main/java/database/BlogsTable.java src/main/java/models/Blog.java src/main/java/Main.java -d build
$ java -classpath "build;src/main/resources/mariadb-java-client-3.2.0.jar;." Main
```