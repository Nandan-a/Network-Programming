#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include<pthread.h>



#define PORT 8080
#define BUFFER_SIZE 1024

int client_fd;
struct sockaddr_in server;
char message[BUFFER_SIZE] = "Hello from client";
int addrlen = sizeof(server);
char buffer[BUFFER_SIZE] = {0};

void * routine1(){
    gets(message);
    send(client_fd, message, strlen(message),0);
    printf("message sent to server.\n");
    read(client_fd, buffer, BUFFER_SIZE);
    printf("server: %s\n",buffer);
}



int main(){
    pthread_t t1,t2,t3,t4;
    //create socket file ddj nykescripter
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
    while(1)
    {
        
    if (pthread_create(&t1, NULL, &routine1, NULL)) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine1, NULL)) {
        return 2;
    }
    if (pthread_create(&t3, NULL, &routine1, NULL)) {
        return 1;
    }
    if (pthread_create(&t4, NULL, &routine1, NULL)) {
        return 2;
    }
    if (pthread_join(t1, NULL)) {
        return 3;
    }
    if (pthread_join(t2, NULL)) {
        return 4;
    }
    if (pthread_join(t3, NULL)) {
        return 3;
    }
    if (pthread_join(t4, NULL)) {
        return 4;
    }
        //receive message from server
       

    }

    close(client_fd);

    return 0;
}
