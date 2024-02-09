#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


void error(const char* msg){
    perror(msg);
    exit(1);
}
void func(int sockfd,int n,char *buffer)
{
while(1) {
bzero(buffer,255);
fgets(buffer,255,stdin);
n = write(sockfd,buffer,strlen(buffer));

if(n<0) error("Error on writing");

bzero(buffer,255);
n = read(sockfd,buffer,255);
if(n<0) error("Error on reading");
printf("Server: %s",buffer);
int i= strncmp("Bye",buffer,3);
if(i==0)   break;
}
}
int main(int argc, char *argv[]) {
int sockfd,portno,n;
struct sockaddr_in serv_addr;
struct hostent *server;

char buffer[256];
if(argc < 3) {
fprintf(stderr,"usage %s hostname port\n", argv[0]);
exit(0);
}
portno = atoi(argv[2]);
// socket create and verification
sockfd = socket(AF_INET, SOCK_STREAM, 0); 
if(sockfd<0) error("socket creation failed...\n"); 
 else printf("Socket successfully created..\n"); 

 server = gethostbyname(argv[1]);
if (server == NULL) fprintf(stderr,"ERROR, no such host\n");
bzero((char *)&serv_addr, sizeof(serv_addr));
// assign IP, PORT 
serv_addr.sin_family = AF_INET;
bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);    

//serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
serv_addr.sin_port = htons(portno);
// connect the client socket to server socket
if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0) {
error("connection with the server failed...\n");
}
else printf("connected to the server..\n");
// function for chat 
func(sockfd,n,buffer);
// close the socket 
close(sockfd);
return 0;
}
