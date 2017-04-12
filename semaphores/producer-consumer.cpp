
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <thread> 
#include <mutex> 
#include <condition_variable>
#include <chrono>
#include <atomic>


using namespace std;

// Memory Vectors
vector<int> sharedMemory; // vector with N positions (full of zeros)
vector<int> consumerMemory;
// Semaphores Variables
mutex s_mutex; // mutex semaphore 
condition_variable s_full;  // semaphore to indicate full shared memory
condition_variable s_empty;  // semaphore to indicate empty shared memory 

int numbersToProcess;
int spaces;
int elements = 0;
atomic<int> p_working(0);
int produced = 0;
int consumed = 0;

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

void produce(int p_id){
	unique_lock<mutex> lock(s_mutex);
	int positionToStore = findEmptyPosition(sharedMemory); // -1 if the vector is full
	if(s_full.wait_for(lock,chrono::milliseconds(200),[] {return elements != spaces ;}) && positionToStore  != -1){
		int product = getRandomNumber(p_id); // p_id is used as part of the seed
		sharedMemory[positionToStore] = product; // putting the number in the memory
		elements += 1;
		produced +=1;
		s_empty.notify_all();
	}
}

void consume(){
	unique_lock<mutex> lock(s_mutex);
	int positionToGet = findProductPosition(sharedMemory); // -1 iff the vector is empty
	if(s_empty.wait_for(lock,chrono::milliseconds(200),[] {return elements > 0;}) && positionToGet  != -1){
		cout << sharedMemory[positionToGet]<< " is prime? The answer is: "<< isPrime(sharedMemory[positionToGet])<< endl;
		consumerMemory.push_back(sharedMemory[positionToGet]); // saving the number in local memory
		sharedMemory[positionToGet] = 0; // cleaning the position after read a number
		elements -= 1;
		consumed +=1;
		s_full.notify_all();
	}
}


void consumer(){
	while(p_working == 0){
		this_thread::yield();
	}
	while(consumed < numbersToProcess){
		consume();
	}
}

void producer(){
	p_working += 1;
	while(produced < numbersToProcess){
		produce(produced);
	}
	p_working -= 1;
}

int main(int argc, char* argv[]) {
	spaces = atoi(argv[1]); // first argument is N, the number os spaces in shared memory
	int numberConsumerThreads = atoi(argv[2]);  // second argument is the number of consumer threads
	int numberProducerThreads = atoi(argv[3]);  // third argument is the number of producer threads

	// Measure of time 
	chrono::time_point<std::chrono::system_clock> start, end;
	start = chrono::system_clock::now();


	int numberOfThreads = numberConsumerThreads+numberProducerThreads;
	numbersToProcess = 1000; // number of numbers that consumer will process
	thread producerConsumerThreads[numberOfThreads];
	// Fill memory vector with the argument spaces
	for (int i = 0; i < spaces; ++i){
		sharedMemory.push_back(0);
	}
	// Launch  Threads
	for(int i = 0; i < numberProducerThreads;i++){
		producerConsumerThreads[i] = thread(producer);
	}
	for(int i = numberProducerThreads; i < numberOfThreads;i++){
		producerConsumerThreads[i] = thread(consumer);
	}
	// Join Threads
	for (int i = 0; i < numberOfThreads;i++){ 
		producerConsumerThreads[i].join();
	}

	end = chrono::system_clock::now();
	long elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();
	cout << elapsed_seconds  << endl;
	return 0;
}