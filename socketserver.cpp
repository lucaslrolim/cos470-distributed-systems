//TCP socket server source
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int checkPrime(int n){
	if(n == 0){
		return 0;
	}
	else if(n >= 2){
		for(int i = 2; i<n; i++){
			if(n%i == 0){ 
				return 0;
			}
		}
	}
	return 1;
}

//display message if system calls fail
void error(const char *msg){ 
	perror(msg);
	exit(1);
}

//handles more than one connection
void handleConnection(int sock){
	int n;
	char buffer[256];
	bzero(buffer,256);
	n = read(sock,buffer,255);
	if(n < 0){
		error("ERROR reading from socket");
	}
	
	cout << "Message: " << buffer << endl;
	n = write(sock, "Message received.", 17);
	if(n < 0){
		error("ERROR writing to socket");
	}
}



int main(int argc, char *argv[]){
	int sockfd, newsockfd;  //file descriptions
	int	portno, clilen, n; //port number of connection, size of address, number of characters
	char buffer[256]; //maybe change to int num[0]
	struct sockaddr_in serv_addr, cli_addr; //internet address
	
	if(argc < 2){
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	
	//create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0){
		error("ERROR opening socket");
	}
	
	bzero((char*) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);  //convert string to int
	
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(portno); //convert portno host byte code to portno network byte code
	serv_addr.sin_addr.s_addr = INADDR_ANY; //IP address
	
	if(bind(sockfd, struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		error("ERROR on binding");
	}
	
	listen(sockfd,5);
	
	clilen = sizeof(cli_addr);
	//process blocked until client connects to server. wakes up when connection established
	
	for(;;){
		newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
		if(newsockfd < 0){
			error("ERROR on accept"); 
		}
		
		//handles more than one connection
		pid = fork();
		if(pid < 0){
			error("ERROR on fork");
		}
		else if(pid == 0){
			close(sockfd);
			handleConnection(newsockfd);
			exit(0);
		}
		else{
			close(newsockfd);
		}
			
		/*
		* ignore SIGCHLD to avoid zombies
		* somewhere around here
		* maybe signal(SIGCHLD,SIG_IGN)?
		*/
		
		//init buffer
		bzero(buffer,256);
		//read from socket. blocks until there is something to read
		n = read(newsockfd, buffer, 255); //maybe change read() to recv()?
		if(n < 0){
			error("ERROR reading from socket");
		}
	
		//connection established
		cout << "Message: " << buffer << endl;
	
		//message to client
		//third arg is size of message
		n = write(newsockfd, "I got your message",18); //maybe change write() to send()?
		if( < 0){
			error("ERROR writing to socket");
		}
	
		close(newsock);
		close(sockfd);
	}
	
	return 0;

}
	
	