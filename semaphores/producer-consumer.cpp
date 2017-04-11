
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

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

int getRandomNumber(){
    srand(time(NULL));
    int number = rand() % 10000000 + 1;
    return number;
}

int findEmptyPosition(vector<int> myVector){
	// return -1 if a vector is full
	int targetPosition = -1;
	int i = 0;
	while(i < myVector.size()){
		if(myVector[i] == 0){
			targetPosition = i;
			break;
		}
		i++;
	}
	return targetPosition;
}

int findProductPosition(vector<int> myVector){
	// return -1 if a vector is empty
	int targetPosition = -1;
	int i = 0;
	while(i < myVector.size()){
		if(myVector[i] != 0){
			targetPosition = i;
			break;
		}
		i++;
	}
	return targetPosition;
}

int main(int argc, char* argv[]) {
	// first argument is N, the number os spaces in shared memory
	// second argument is the number of consumer threads
	// third argument is the number of producer threads


	vector<int> sharedMemory (atoi(argv[1]),0); // vector with N positions (full of zeros)
	vector<int> consumerMemory;
	int numbersToProcess = 1000; // number of numbers that consumer will process

	/// TEMPORARIAMENTE TESTANTANDO COM APENAS 2 THREADS
	int pidStatus = fork();
    if (pidStatus == -1){
        perror("Error creating child process.");
        exit(1);
	}
	///
	if(pidStatus > 0){
		// PRODUCER
		while (true){
			int positionToStore = findEmptyPosition(sharedMemory); // -1 if the vector is full
			if(positionToStore != -1){ // MUDAR ESSA CONDIÇÃO PARA SEMÁFORO
				int product = getRandomNumber();
				sharedMemory[positionToStore] = product; // putting the number in the memory
			}
		}
	}
	else{
		// CONSUMER
		while(numbersToProcess > 0){
			int positionToGet = findProductPosition(sharedMemory); // -1 iff the vector is empty
			if(positionToGet != -1){ // MUDAR ESSA CONDIÇÃO PARA SEMÁFORO
				cout << sharedMemory[positionToGet]<< " is prime? The answer is: "<< isPrime(sharedMemory[positionToGet])<< endl;
				consumerMemory.push_back(sharedMemory[positionToGet]); // saving the number in local memory
				sharedMemory[positionToGet] = 0; // cleaning the position after read a number
				numbersToProcess -= 1;
			}
		}
	}
	return 0;
}