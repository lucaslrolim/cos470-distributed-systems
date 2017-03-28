#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>      //read()-write()
#include <netdb.h>
//#include <netinet/in.h>

using namespace std;

bool isPrime(int number){
    int i;
    for (i=2; i<number; i++){
        if (number % i == 0){
            return false;
        }
    }
    return true;
}


int main(int argc, char *argv[]){
	int socketfd, auxsocketfd; //file descriptors
	int buffer; //holds numbers to be avaliated
	int portNum = 6000; //arbitrary port for socket
	bool num; //auxiliary variable
	int allowedCons = 1; //number of allowed client communications at a given time
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;

	//returns socket descriptor. -1
	socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //on error
	if(socketfd < 0){
		perror("ERROR opening socket.");
		exit(1);
	}

	//places n null bytes in string s. used to set all the socket
	//structures with null values
	//does not return anything
	//Initializing socket structure
	bzero((char*)&serverAddr, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;  //Internet standard
	serverAddr.sin_port = htons(portNum);  //converts host internal data representation to Network Byte Order (standard). set to 0 for random assignment
	serverAddr.sin_addr.s_addr = INADDR_ANY; //server's IP is auto-assigned

	//(TCP only) assings local(host) protocol address to a socket
	//returns 0 if successful. -1 on error
	if(bind(socketfd, (struct socketAddr*)&serverAddr, sizeof(struct serverAddr))<0){
		perror("ERROR on binding.");
		exit(1);
	}


	//(TCP only) converts unconnected socket into passive socket
	//i.e. accept incoming connection requests to this socket
	//returns 0 if successful. -1 on error
	listen(socketfd, allowedCons);



	while(true){ //buffer>0
		//(TCP only) returns the next completed connection from queue
		//queue handled by OS
		//returns non-negative descriptor on success. -1 on error
		//returned descriptor assumed to be client socket descriptor
		//read-write operations will be done on this descriptor
		auxsocketfd = accept(socketfd,(struct socketAddr*) &clientAddr,&(sizeof(clientAddr)))
		if(auxsocketfd < 0){
			perror("ERROR on accepting.");
			exit(1);
		}

		//attempts to read n bytes from file(socket) associated with buffer
		//into the buffer pointed to by bufptr
		read(auxsocketfd, &buffer, sizeof (int));
		if(buffer == 0){
			break;
		}

		//server processing
		num = isPrime(buffer);

		//attempts to write n bytes from buffer pointer to the file(socket)
		//returns number of bytes written. -1 on error
		write(auxsocketfd, &num, sizeof (int));
	}
	cout << "0 received from Producer. Terminating process." << endl;

	//close communication between client and server
	//0 on success. -1 on error
	close(socketfd);
	return 0;
}