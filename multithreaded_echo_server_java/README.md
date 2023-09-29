# Multi-threaded Echo Server in Java

### Build Instructions

```bash
$ javac src/main/java/Client.java src/main/java/Server.java src/main/java/RequestHandler.java -d build
$ java -classpath build Server      # To start server
$ java -classpath build Client      # To start client
```