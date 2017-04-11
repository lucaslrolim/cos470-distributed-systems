
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include <thread> 
#include <mutex> 

using namespace std;
vector<int> sharedMemory; // vector with N positions (full of zeros)
vector<int> consumerMemory;

bool isPrime(int number){
    int i;
    for (i=2; i<number; i++){
        if (number % i == 0){
            return false;
        }
    }
    return true;
}

int getRandomNumber(int p){
    srand(p+time(NULL));
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

void producer(int p_id){
	int positionToStore = findEmptyPosition(sharedMemory); // -1 if the vector is full
	if(positionToStore != -1){ // MUDAR ESSA CONDIÇÃO PARA SEMÁFORO
		int product = getRandomNumber(p_id); // p_id is used as part of the seed
		sharedMemory[positionToStore] = product; // putting the number in the memory
	}
}

void consumer(vector<int> sharedMemory,vector<int> &consumerMemory, int &numbersToProcess){
	int positionToGet = findProductPosition(sharedMemory); // -1 iff the vector is empty
	if(positionToGet != -1){ // MUDAR ESSA CONDIÇÃO PARA SEMÁFORO
		cout << sharedMemory[positionToGet]<< " is prime? The answer is: "<< isPrime(sharedMemory[positionToGet])<< endl;
		consumerMemory.push_back(sharedMemory[positionToGet]); // saving the number in local memory
		sharedMemory[positionToGet] = 0; // cleaning the position after read a number
		numbersToProcess -= 1;
	}
}



int main(int argc, char* argv[]) {
	int spaces = atoi(argv[1]); // first argument is N, the number os spaces in shared memory
	int numberConsumerThreads = atoi(argv[2]);  // second argument is the number of consumer threads
	int numberProducerThreads = atoi(argv[3]);  // third argument is the number of producer threads
	int numberOfThreads = numberConsumerThreads+numberProducerThreads;
	int numbersToProcess = 1000; // number of numbers that consumer will process
	//thread consumerThread[numberConsumerThreads]; // creating consmer threads
	//thread producerThread[numberProducerThreads]; // creating producer threads
	thread producerConsumerThreads[numberOfThreads];
	mutex s_mutex; // mutex semaphore 
	// FIll memory vector with the argument spaces
	for (int i = 0; i < spaces; ++i){
		sharedMemory.push_back(0);
	}

	// Launch  Threads
	for(int i = 0; i < numberProducerThreads;i++){
		producerConsumerThreads[i] = thread(producer,i);
	}
	//for(int i = ProducerThreads; i < numberOfThreads;i++){
	//	producerConsumerThreads[i] = thread(consumer,sharedMemory,consumerMemory);
	//}
	// Join Threads
	for (int i = 0; i < numberProducerThreads;i++){ // test only producers
		producerConsumerThreads[i].join();
	}

	// TEST SHARED MEMORY

	for(int i = 0; i < spaces;i++){
		cout << sharedMemory[i]<< endl;
	}
	return 0;
}