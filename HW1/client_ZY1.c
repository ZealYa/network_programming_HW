#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define PORT 5200   //server PORT
#define MAXDATASIZE 100   //buffer max size
int main(int argc,char *argv[]){
  int sockfd,numbytes;
  char buf[MAXDATASIZE];
  struct hostent *he;
  struct sockaddr_in server;
  if(argc!=2){
    printf("User:%s <IP address>\n",argv[0]);
    exit(-1);
  }
  if((he=gethostbyname(argv[1]))==NULL){
    perror("GetHostByName error.");
    exit(-1);
  }
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
    perror("Create Socket Failed.");
    exit(-1);
  }
  bzero(&server,sizeof(server));
  server.sin_family=AF_INET;
  server.sin_port=htons(PORT);
  server.sin_addr=*((struct in_addr *)he->h_addr);
  if(connect(sockfd,(struct sockaddr *)&server,sizeof(struct sockaddr))==-1){
    perror("Connection Failed.\n");
    exit(1);
  }
  printf("Connection Success.\n");
  close(sockfd);
}