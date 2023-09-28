#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT 8080
#define LBR '\n'

int main( int argc , char** argv ) {

    int serverFD = 0;
    int socketFD = 0;

    // socket address structure specific for
    // IPv4 protocol
    struct sockaddr_in address ; 

    // AF_INET: Address Family for IPv4
    // SOCK_STREAM: Socket for streaming
    // 0 => protocol decided by service provider
    serverFD = socket( AF_INET , SOCK_STREAM , 0 ) ; 
    if( serverFD >= 0 ) {

        // htons => numbers to network bytes (little-endian)
        address.sin_port =  htons( PORT ) ; 
        address.sin_family = AF_INET ; 
        address.sin_addr.s_addr = INADDR_ANY ;

        int bindResult = bind( serverFD , (struct sockaddr*) &address , sizeof( address ) ) ; 
        if( bindResult >= 0 ) {
            int listenResult = listen( serverFD , 5 ) ; 
            if( listenResult >= 0 ) {
                socketFD = accept( serverFD , (struct sockaddr*) &address , (socklen_t*) sizeof(address) ) ;
                if( socketFD >= 0 ) {
                    std::cout << "server Connection accepted" << LBR ; 
                }
                else {
                    std::cout << "Could not accept connection" << LBR ; 
                }
            }
            else {
                std::cout << "Could not listen on socket" << LBR ; 
            }
        }
        else {
            std::cout << "Could not bind to socket" << LBR ; 
        }
    }
    else {
        std::cout << "Could not connect to server socket." << LBR ; 
    }

    return 0;
}