#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <unistd.h>      //read()-write()
#include <netdb.h>
#include <netinet/in.h>
#include <time.h>

using namespace std;

int getRandomNumber(int base = 0){
	srand(time(NULL));
    int number = rand() % 100 + 1;
    if(number <= base){
        number += base;
    }
    return number;
}

int main(int argc, char* argv[]){
	int socketfd; //file descriptor
	int randomNum; //holds numbers to be avaliated
	bool buffer;
	int portNum = 6000;
	int iterations = atoi(argv[1]);
	int zero = 0;
	//char* s;
	struct sockaddr_in serverAddr; //reference to socket's info
	struct hostent *server; //information related to server

	//returns socket descriptor. -1 on error
	socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socketfd < 0){
		perror("ERROR opening socket.");
		exit(1);
	}
	
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host.\n");
		exit(0);
    }
	
	//places n null bytes in string s. used to set all the socket
	//structures with null values
	//does not return anything
	//Initializing socket structure
	bzero((char*)&serverAddr, sizeof(serverAddr));
	
	serverAddr.sin_family = AF_INET;  //Internet standard
	serverAddr.sin_port = htons(portNum);  //converts host internal data representation to Network Byte Order (standard). set to 0 for random assignment
	//s = &serverAddr.sin_addr.s_addr; //server's IP
	//copies n bytes from left string to right string. 
	//Overlapping strings are handled correctly.
	bcopy((char*)server->h_addr, (char*)&serverAddr.sin_addr.s_addr, sizeof(serverAddr));
	
	//(TCP only) establish connection with a server
	//returns 0 if successful. -1 on error
	if(connect(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
		perror("ERROR trying to connect.");
		exit(1);
	}
	
	randomNum = getRandomNumber();
	
	for(int i=0; i<iterations; i++){
		cout << "Sendind number: " << randomNum << endl;
		
		//attempts to write n bytes from buffer pointer to the file(socket)
		//returns number of bytes written. -1 on error
		write(socketfd, &randomNum, sizeof(int));
		
		//attempts to read n bytes from file(socket) associated with buffer
		//into the buffer pointed to by bufptr
		read(socketfd, &buffer, 1);
		
		cout << "Received result: " << buffer << endl;
		//new bigger randomnum
		randomNum = getRandomNumber(randomNum);
	}
	
	write(socketfd, &zero, sizeof(int));
	cout << "Warning Consumer to terminate. Terminating." << endl;
	
	//close communication between client and server
	//0 on success. -1 on error
	close(socketfd);
	return 0;
}