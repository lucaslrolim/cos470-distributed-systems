#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <iostream>
#include <string>

using namespace std;

// SIGKILL (9) and SIGSTOP(19) can't be handled
const string signalTypes[] = {"SIGHUP","SIGINT","SIGQUIT","SIGILL","SIGTRAP",
                               "SIGABRT","SIGBUS","SIGFPE","SIGUSR1","SIGSEGV",
                               "SIGUSR2","SIGPIPE","SIGALRM","SIGTERM","SIGSTKFLT",
                               "SIGCHLD","SIGCONT","SIGTSTP","SIGTTIN","SIGTTOU",
                                "SIGURG","SIGXCPU","SIGXFSZ","SIGVTALRM","SIGPROF",
                                "SIGWINCH","SIGIO","SIGPWR","SIGSYS"};

const string signalNames[] = {"Hangup (POSIX)","Interrupt (ANSI)","Quit (POSIX)","Illegal Instruction (ANSI)",
                            "Trace trap (POSIX)","Abort (ANSI)","BUS error (4.2 BSD)","Floating-Point arithmetic Exception (ANSI)",
                            "User-defined signal 1","Segmentation Violation (ANSI)","User-defined signal 2","Broken pipe (POSIX)",
                            "Alarm clock (POSIX)","Termination (ANSI)","Stack fault","Child status has changed (POSIX","Continue (POSIX)",
                            "Keyboard stop (POSIX)","Background read from tty (POSIX)","Background write to tty (POSIX)","Urgent condition on socket (4.2 BSD)",
                            "CPU limit exceeded (4.2 BSD)","File size limit exceeded (4.2 BSD)","Virtual Time Alarm (4.2 BSD)",
                            "Profiling alarm clock (4.2 BSD)","Window size change (4.3 BSD, Sun)","I/O now possible (4.2 BSD)",
                            "Power failure restart (System V)","Bad system call"};


// Handler catch the  signal and show his value number and description
void signalHandler(int signum) {
    cout << "Caught signal: " << signalTypes[signum-1] <<" described as "<< signalNames[signum-1] << endl;
    // Signal  1 ends the process
    if (signum == 1){
        exit(signum);
    }
}

int main() {

    // Register signal and signal handler
    for (int i=0;i < 30;i++){
        signal(i, signalHandler);
    }

    cout << "This process is son of process: " << getppid() << endl;
    while(1) {
        cout << "Handler running at process " << getpid() <<endl;
        sleep(1);
    }
    return EXIT_SUCCESS;
}