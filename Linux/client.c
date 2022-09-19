#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define COMMAND_LIMIT 1024
//#define RECEIVE_LIMIT 500
#define zero(_P) memset(&_P,0,sizeof(_P))
int main(int argc, char **argv){
    if(argc==1){
        puts("format: [executable] [port]");
        return 0;
    }
    int port=atoi(*(argv+1));
    char send_buffer[COMMAND_LIMIT+1];
    //char receive_buffer[RECEIVE_LIMIT];
    struct sockaddr_in server;
    zero(server);
    server.sin_family=AF_INET;    
    server.sin_addr.s_addr=htonl(INADDR_ANY); 
    server.sin_port=htons(port);
    int listener, connector;
    listener=socket(AF_INET, SOCK_STREAM, 0);
    bind(listener, (struct sockaddr*)&server,sizeof(server));
    if(listen(listener, 1) == -1){
        puts("Failed to listen");
        return -1;
    }
    connector=accept(listener, (struct sockaddr*)NULL ,NULL);
    puts("Host found."); 
    while(1){
        puts("Enter command:");
        fgets(send_buffer,COMMAND_LIMIT,stdin);
        int wrlen=write(connector,send_buffer,strlen(send_buffer));
        if(wrlen==-1){
            printf("Connection has been closed. Stopping program.");
            close(connector);
            return 0;
        }
    }
    return 0;
}