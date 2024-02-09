#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include<unistd.h>

void error(const char* msg){
    perror(msg);
    exit(1);
}
// Function designed for chat between client and server.
void func(int newsockfd,int n,char *buffer) {
  
    // infinite loop for chat 
while(1){
    bzero(buffer,  255); 
    n = read(newsockfd, buffer, 255);
    if(n<0){
        error("Error on reading");
    }  
    printf("Client: %s\n", buffer);
    bzero(buffer, 255);
    fgets(buffer, 255, stdin);
    n = write(newsockfd, buffer, strlen(buffer));
    if(n<0){
        error("Error on writing");
    }
    int i = strncmp("Bye", buffer, 3);
    if(i == 0){
        break;
    }
}
}
// Driver function
int main(int argc,  char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Port number not provided. Program terminated\n");
        exit(1);
    }
int sockfd, newsockfd,portno,n;
char buffer[255];
struct sockaddr_in serv_addr, cli_addr;
socklen_t clilen;
// socket create and verification
sockfd = socket(AF_INET, SOCK_STREAM, 0); 
if (sockfd <0)
{
    printf("socket creation failed...\n");
    exit(0);
 }
else printf("Socket successfully created..\n");
bzero((char *)&serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);
// assign IP, PORT
serv_addr.sin_family = AF_INET; 
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
serv_addr.sin_port = htons(portno);
// Binding newly created socket to given IP and verification 
if ((bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))<0) {
    error("socket bind failed...\n"); 
}
else printf("Socket successfully binded..\n");
// Now server is ready to listen and verification 
if((listen(sockfd, 5)) != 0)
{
printf("Listen failed...\n");
exit(0); 
}
else
printf("Server listening..\n");
 clilen = sizeof(cli_addr);


// Accept the data packet from client and verification 
newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
if (newsockfd < 0)
{
printf("server accept failed...\n"); exit(0);
} else
printf("server accept the client...\n");


// Function for chatting between client and server 
func(newsockfd,n,buffer);


 close(newsockfd);
    close(sockfd);
    return 0;
}