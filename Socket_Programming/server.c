#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include <asm-generic/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_fd,new_socket;
    struct sockaddr_in server,client;
    int opt=1;
    int addrlen = sizeof(server);
    char *buffer[BUFFER_SIZE]={0};
    char *temp_buffer[BUFFER_SIZE];

    //Create socket file descriptor
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    //Forcefully attaching socket to the port 8080
    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))){
        perror("Setsocket failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    //Bind the Socket
    if(bind(server_fd,(struct sockaddr *)&server,sizeof(server))<0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    //Listen for incoming connections
    if(listen(server_fd,3)<0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n",PORT);

    //Accept incoming connection
    int count =0;
    char msg[3] = "Bye";
    while(count!=3){
        if((new_socket=accept(server_fd,(struct sockaddr *)&client,(socklen_t*)&addrlen))<0){
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        
        read(new_socket,buffer,BUFFER_SIZE);
        printf("Client: %s\n",buffer);
    }


    //Read message from client and send it back

    send(new_socket,buffer,strlen(buffer),0);
    printf("Message sent back to client.\n");

    // close(server_fd);
    return 0;
}