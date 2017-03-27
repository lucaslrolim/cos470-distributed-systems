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


#define BUFFER 100


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
    int inferiorLimit = 0; // Always generate random numbers bigger than this limit
    char str[BUFFER];

    // Dealing with erros on pipe
    if(status == -1){
        perror("Pipe error.");
        return -1;
    }

    // Dealing with fork error and creating child process
    int pidStatus = fork();
    if (pidStatus == -1){
        perror("Error creating child process.");
        exit(1);
    }

    int numberToProduce = atoi(argv[1]);
    int wait = 0;
    if(pidStatus > 0){
    // PRODUCER
        for(int i = 0;i < numberToProduce;i++){
            int product = getRandomNumber(inferiorLimit);
            inferiorLimit = product;
            const char * c = to_string(product).c_str();
            string number = c;
            cout << "Producer send: " << number << endl;
            write(fd[1], c, sizeof(str) + 1);
            sleep(1);
        }
        cout << "All products were sent" << endl;
        write(fd[1], "0", sizeof("0")+1);
        close(fd[1]);
        exit(0);
    }
    else{
    // CONSUMER
        while(true){
            char str_recebida[BUFFER];
            read(fd[0], str_recebida, sizeof(str_recebida));
            int number = atoi(str_recebida);
            if (number == 0){
                break;
            }
            cout << "Consumer received: " << str_recebida << endl;
            bool prime = isPrime(number);
            cout << "Number " << str_recebida << " is prime: " << prime << endl;
        }
        cout << "Consumer received 0. Finishing process..." << endl;
        close(fd[0]);
        exit(0);
    }
}