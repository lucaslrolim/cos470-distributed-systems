#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h>

using namespace std;


int main(int argc, char* argv[]) {

    int status = kill( atoi(argv[1]), atoi(argv[2]));;
    switch(status){
        case -1:
            cout << "Error sending signal " << argv[1]<<". Process " << argv[2] << " doesn't exist" << endl;
            break;
        case 0:
             cout << "Sent signal " << argv[1] << " to process " << argv[2] << endl;
             break;

    }

    return 0;
}