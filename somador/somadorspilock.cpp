#include <stdlib.h>
#include <iostream>
#include <math.h>
//#include <time.h>
#include <chrono>
#include <atomic>
#include <pthread> //posix thread for unix multi-platforming. does NOT work on windows
//#inlcude <thread> //C++ thread library. implemented using pthread. "easier to code"
using namespace std;

class Spinlock{
    //using atomic_flag as a lock
    std::atomic_flag l = ATOMIC_FLAG_INIT;
public:
        void aquire(){
            while(l.test_and_set()){} //maybe implement with if?
        }
        void release(){
            l.clear();
        }
};

Spinlock lock;


long int N[] = {10000000, 100000000, 1000000000)};  //amount of numbers(10^7, 10^8, 10^9)
int K[] = {1,2,4,8,16,32,64,128,256};              //number of threads
vector<char> values;  //vector to contain N numbers, each of 1 byte

int p;               //'portion' of the vector "values"
long int acc = 0;    //'accumulator' holds the final sum

//if using <thread>, rewrite this function
void *create_thread(void *x){
    long threadId = (long)x;
    int sum = 0;
    int init = p*threadId;
    for(long int i=0; i<p; i++){
        if((i+init) >= N){
            break;
        }
        sum = sum + values[i+init];
    }
    lock.aquire();
    acc = acc + sum;
    lock.release();
    pthread_exit(NULL);
}


int main(int argc, char** argv){
    //time variables
    //pair inicio-fim: time to do a {N,K} combination
    //pair before-after: time to fill the vector with random numbers
    //pair hajime-owari: total time of the program execution
    chrono::time_point<chrono::system_clock> t_inicio, t_fim, t_before, t_after, t_hajime, t_owari;
    t_hajime = chrono::system_clock::now();
    //1->2->4->...->256
    for(int j=0; j<8; j++){
        //first 10^7 then 10^8 then 10^9
        //(sizeof(N)/sizeof(N[0]) = 3
        for(int i=0; i<3; i++){
            t_inicio = chrono::system_clock::now();
            //reserve memory. values can have N[i] elements
            values.reserve(N[i]);

            t_before = chrono::system_clock::now();
            //fill vector
            for(long int a=0; a<N[i]; a++){
                values[a] = char((rand()%201) - 100); //random number in [-100,100]
            }
            t_after = chrono::system_clock::now();
            //dividing portions according to number of threads
            p = trunc(N[i]/K[j]);
            if((N%K))!=0){
                p++;
            }

            pthread_t threads[K[j]; //contains created threads
            for(long l=0; l<K[j]; l++){
                if((pthread_create(&threads[l], NULL, &create_thread, (void*)i))!=0){
                    cout<<"Thread creation failed."<<endl;
                }
            }
            //wait for each thread to complete
            for(int b=0; b<K; b++){
                pthread_join(threads[b], NULL);
            }
            t_fim = chrono::system_clock::now();
            cout<<"N: "<<N[i]<<"; ";
            cout<<"K: "<<K[j]<<"; ";
            cout<<"Sum: "<<acc<<"; ";
            cout<<"Vector time: "<<(t_after-t_before)<<"; ";
            cout<<"Process time: "<<(t_fim-t_inicio)<<endl;

        }
    }
    t_owari = chrono::system_clock::now();
    cout<<"End of program."<<endl;
    cout<<"Total time elapsed: "<<(t_owari-t_hajime)<<endl;
    return 0;
}
