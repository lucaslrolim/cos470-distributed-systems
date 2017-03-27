#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <sstream>
using namespace std;


#define stringSize 100


bool isPrime(int number){
    int i;
    for (i=2; i<number; i++){
        if (number % i == 0){
            return false;
        }
    }
    return true;
}

int getRandomNumber(int base = 0){
    srand(time(NULL));
    int number = rand() % 100 + 1;
    if(number <= base){
        number += base;
    }
    return number;
}

int main(int argc, char* argv[]) {


    int fd[2]; // File descriptors for Pipe
    pid_t pid; // Store PID number
    int status = pipe(fd); // Flag to errors
    int inferiorLimit = 0; // Always generate random number bigger than that
    char readPipe[100];

    // Dealing with erros on pipe
    if(status == -1){
        perror("Pipe error.");
        return -1;
    }

    int pidStatus = fork();
    // Dealing with fork error and creating child process
    if (pidStatus == -1){
        perror("Error creating child process.");
        exit(1);
    }

    //int numberToProduce = atoi(argv[1]);
    int numberToProduce = 4;

    if(pidStatus > 0){
        for(int i = 0;i < numberToProduce;i++){
            int product = getRandomNumber(inferiorLimit);
            inferiorLimit = product;
            const char * c = to_string(product).c_str();
            string number = c;
            cout << "Producer send: " + number << endl;
            write(fd[1], c, number.size() + 1);
            sleep(1);
        }
        cout << "All products were sended" << endl;
        write(fd[1], "0", 2);
        close(fd[1]);
        exit(0);
    }
    else{
        while(true){
            char str_recebida[stringSize];
            read(fd[0], str_recebida, stringSize);
            string numericString = str_recebida;
             cout << str_recebida<< endl;
            int number = atoi(numericString.c_str());
            if (number == 0){
                break;
            }
            cout << "Consumer receive: " + numericString << endl;
            bool prime = isPrime(number);
            cout << "Number " + numericString + " is prime: " << prime << endl;
        }
        cout << "Consumer received 0. Finishing process..." << endl;
        close(fd[0]);
        exit(0);
    }
}