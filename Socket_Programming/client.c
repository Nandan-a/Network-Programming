#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <asm-generic/socket.h>


#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int client_fd;
    struct sockaddr_in server;
    char message[BUFFER_SIZE];
    int addrlen = sizeof(server);
    char* buffer[BUFFER_SIZE] = {0};
    while(1){
    gets(message);
    //create socket file descripter
    if((client_fd = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Convert IPv$ and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET,"127.0.0.1",&server.sin_addr)<=0)
    {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    //connect to the server 
    if(connect(client_fd,(struct sockaddr *)&server, sizeof(server))<0)
    {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    //send message to server
    send(client_fd, message, strlen(message),0);
    printf("message sent to server.\n");
    
    send(client_fd, message, strlen(message),0);
    printf("message sent to server.\n");
    }

    
    //receive message from server
    read(client_fd, buffer, BUFFER_SIZE);
    printf("server: %s\n",buffer);

    close(client_fd);

    return 0;
}