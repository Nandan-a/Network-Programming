#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include <asm-generic/socket.h>
#include<pthread.h>


#define PORT 8080
#define BUFFER_SIZE 1024

int server_fd,new_socket;
struct sockaddr_in server,client;
int opt=1;
int addrlen = sizeof(server);
char *buffer[BUFFER_SIZE]={0};
char *temp_buffer[BUFFER_SIZE];

void* routine() {    
    //Read message from client and send it back
    read(new_socket,buffer,BUFFER_SIZE);
    printf("Client: %s\n",buffer);
    gets(buffer);
    send(new_socket,buffer,strlen(buffer),0);
    printf("Message sent back to client.\n");
}



int main(){
    pthread_t t1,t2,t3,t4;

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

        if((new_socket=accept(server_fd,(struct sockaddr *)&client,(socklen_t*)&addrlen))<0){
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
    //Accept incoming connection
    while(1){

    if (pthread_create(&t1, NULL, &routine, NULL)) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, NULL)) {
        return 2;
    }
    if (pthread_create(&t3, NULL, &routine, NULL)) {
        return 1;
    }
    if (pthread_create(&t4, NULL, &routine, NULL)) {
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

        
    
    }


    // close(server_fd);
    return 0;
}