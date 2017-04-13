#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <atomic>
//#include <pthread> //posix thread for unix multi-platforming. does NOT work on windows
#include <thread> //C++ thread library. implemented using pthread. "easier to code". works on windows
#include <vector>
#include <fstream>
using namespace std;

class Spinlock{
    //using atomic_flag as a lock
    std::atomic_flag l = ATOMIC_FLAG_INIT;
public:
        void aquire(){
            while(l.test_and_set()){
                //nothing
            }
        }
        void release(){
            l.clear();
        }
};

Spinlock lock;

//writes output data to .csv
void dataToCSV(int N, int K, double vTime, double pTime){
    ofstream myfile;
      myfile.open("spinlock.csv", ios_base::app);
      myfile<<N<<';'<<K<<';'<<vTime<<';'<<pTime<<endl;
      myfile.close();
}


long int N[] = {10000000, 100000000, 1000000000};  //amount of numbers(10^7, 10^8, 10^9)
int K[] = {1,2,4,8,16,32,64,128,256};              //number of threads
vector<char> values;  //vector to contain N numbers, each of 1 byte

int p;               //'portion' of the vector "values"
long int acc = 0;    //'accumulator' holds the final sum

//if using <thread>, rewrite this function
void sum_thread(long threadId, int n){
    //generating Id's for better manipulation
    //easier than using their actual Id's
    int sum = 0;
    int aux = p*threadId;
    for(long int i=0; i<p; i++){
        if((i+aux) >= n){
            break;
        }
        sum = sum + values[i+aux];
    }
    lock.aquire();
    acc = acc + sum;
    lock.release();
    pthread_exit(NULL);
}


int main(int argc, char** argv){
    //time variables
    //pair inicio-fim: time to do one, and only one, {N,K} combination
    //pair before-after: time to fill the vector with random numbers
    //pair hajime-owari: total time of the program execution
    chrono::time_point<chrono::system_clock> t_inicio, t_fim, t_before, t_after, t_hajime, t_owari;
    t_hajime = chrono::high_resolution_clock::now();
    //1->2->4->...->256
    for(int j=0; j<8; j++){
        //first 10^7 then 10^8 then 10^9
        //(sizeof(N)/sizeof(N[0]) = 3
        for(int i=0; i<3; i++){
                //ten times each {N,K}
                t_inicio = chrono::high_resolution_clock::now();
                //reserve memory. values can have N[i] elements
                values.reserve(N[i]);

                t_before = chrono::high_resolution_clock::now();
                //fill vector
                for(long int a=0; a<N[i]; a++){
                    values[a] = char((rand()%201) - 100); //random number in range [-100,100]
                }
                t_after = chrono::high_resolution_clock::now();
                //dividing portions according to number of threads
                p = trunc(N[i]/K[j]);
                float r = (N[i]%K[j]);
                if(r!=0){
                    p++;
                }

                for(int times=0; times<10; times++){

                    vector<thread> threads(K[j]); //contains created threads
                    //initiating additions
                    for(long l=0; l<K[j]; l++){
                        threads[l] = thread(sum_thread,l,N[i]);//thread threads[l] (sum_thread,l,N[i]);
                    }
                    //wait for each thread to complete
                    for(int b=0; b<K[j]; b++){
                        threads[b].join();
                    }
                    t_fim = chrono::high_resolution_clock::now();

                    auto t0 = chrono::duration_cast<chrono::microseconds>(t_after-t_before);
                    auto t1 = chrono::duration_cast<chrono::microseconds>(t_fim-t_inicio);

                    cout<<"N: "<<N[i]<<", ";
                    cout<<"K: "<<K[j]<<", ";
                    cout<<"Total: "<<acc<<", ";
                    cout<<"Vector time: "<<t0.count()<<", ";
                    cout<<"Process time: "<<t1.count()<<endl;
                    dataToCSV(N[i], K[j], t0.count(), t1.count());
            }
            acc = 0;
        }
    }
    t_owari = chrono::high_resolution_clock::now();
    auto t2 = chrono::duration_cast<chrono::microseconds>(t_owari-t_hajime);
    cout<<"End of program."<<endl;
    cout<<"Total time elapsed: "<<t2.count()<<"us"<<endl;
    return 0;
}
