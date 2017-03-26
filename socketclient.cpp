//TCP socket client source
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

void error(const char *msg){ 
	perror(msg);
	exit(0); //maybe 1?
}

int main(int argc, char *argv[]){
	int sockfd; //file description
	int	portno, n; //port number, number of characters
	struct sockaddr_in serv_addr;
	struct hostent *server; //pointer to struct defined in netdb.h
	
	char buffer[256]; //maybe change to int num[0]
	
	if(argc < 3){
		fprintf(stderr, "Usage %s hostname port", argv[0]);
		exit(0); //maybe 1?
	}
	
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		error("ERROR opening socket");
	}
	
	server = gethostbyname(argv[1])
	if(server == NULL){
		fprintf(stderr, "ERROR, could not locate host");
		exit(0);
	}
	
	//maybe change bzero to *memset(void *tobeset, int value, size_t nbytes)
	//maybe change bcopy to *memmove(void *target, const void *source, size_t nbytes)
	bzero((char*)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(potno);
	if(connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0){
		error("ERROR connecting");
	}
	
	cout << "Please enter message: "; //prompts user
	bzero(buffer,256);
	fgets(buffer, 255, stdin); //reads message
	n = write(sockfd, buffer, strlen(buffer)); //writes message to socket
	if(n <0){
		error("ERROR writing to socket");
	}
	
	bzero(buffer, 256);
	n = read(sockfd, buffer, 255);
	if(n < 0){
		error("ERROR reading from socket");
	}
	cout << buffer;
	
	return 0;
}
	