
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

main(int argc,char*argv[])

{
     
      int sockfd;
      struct sockaddr_in serv_addr;
      char message[]="PICT";

      serv_addr.sin_family=AF_INET;
      serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
      serv_addr.sin_port=htons(6000);


     if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
     printf("can not create socket");

     if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
     printf("client:can't connect to server");
 
     printf("Enter message");
     scanf("%s",message);

     write(sockfd,message,sizeof(message)); 

     read(sockfd,message,50);

     printf("Getting message from server %s",message);

     close(sockfd);

}
     
