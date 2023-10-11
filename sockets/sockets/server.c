
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>



main(int argc,char  *argv[])
{

	int sockfd,newsockfd,clilen,childpid;
        struct sockaddr_in cli_addr,serv_addr;
        char message[20];

        if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
         printf("server can't open stream socket");

        bzero((char *)&serv_addr,sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        serv_addr.sin_port=htons(6000);

	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
         printf("error in socket");

        listen(sockfd,5);

        clilen=sizeof(cli_addr);

        newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);

        read(newsockfd,message,50);

        printf("Getting message from client %s",message);

        write(newsockfd,message,sizeof(message));

        close(sockfd);

}
     
