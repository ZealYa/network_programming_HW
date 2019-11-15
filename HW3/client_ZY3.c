#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT 5200 //server PORT
#define MAXDATASIZE 1000  //buffer max size
int main(int argc,char *argv[]){
  int fd,numbytes,scan_state;
  char buffer[MAXDATASIZE];
  struct hostent *host;
  struct sockaddr_in server;
  if(argc!=2){
    printf("Usage:%s <IP address>\n",argv[0]);
    return 1;
  }
  if((host=gethostbyname(argv[1]))==NULL){
    perror("Get host by name failed!");
    return 1;
  }
  if((fd=socket(AF_INET,SOCK_STREAM,0))==-1){
    perror("Create socket failed!");
    return 1;
  }
  bzero(&server,sizeof(server));
  server.sin_family=AF_INET;
  server.sin_port=htons(PORT);
  server.sin_addr=*((struct in_addr *)host->h_addr);
  if(connect(fd,(struct sockaddr *)&server,sizeof(struct sockaddr))==-1){
    perror("Connection failed.");
    return 1;
  }
  if(((numbytes=recv(fd,buffer,MAXDATASIZE,0))==-1)){
    perror("recv error.");
    return 1;
  }
  buffer[numbytes]='\0';
  printf("Server message:%s\n",buffer);
  printf("Input your name:");
  if((scan_state=scanf("%s",buffer))==-1){
      printf("break\n");
      close(fd);
  }
  numbytes=strlen(buffer);
  send(fd,buffer,numbytes,0);
  if(((numbytes=recv(fd,buffer,MAXDATASIZE,0))==-1)){
    perror("recv error.");
    return 1;
  }
  buffer[numbytes]='\0';
  printf("%s\n",buffer);
  while(1){
    printf("Input some words:");
    
    if((scan_state=scanf("%s",buffer))==-1){
      printf("Client receive data failed!\n");
      break;
    }
    numbytes=strlen(buffer);
    send(fd,buffer,numbytes,0);
    if(((numbytes=recv(fd,buffer,MAXDATASIZE,0))==-1)){
      perror("recv error.");
      return 1;
    }
    buffer[numbytes]='\0';
    printf("%s\n",buffer);
  }
  close(fd);
}