#include <time.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <semaphore.h>
#include <bits/stdc++.h>
using namespace std;

static int int_count = 0, max_int = 5;
static struct sigaction siga;

static void multi_handler(int sig, siginfo_t *siginfo, void *context) {
    // get pid of sender,
    pid_t sender_pid = siginfo->si_pid;

    if(sig == SIGUSR1) {
        int_count++;
        printf("INT(%d), from [%d]\n", int_count, (int)sender_pid);
        return;
    } else if(sig == SIGQUIT) {
        printf("Quit, bye, from [%d]\n", (int)sender_pid);
        exit(0);
    }

    return;
}

int main(){
    int pid = getpid();
    cout << pid ;
    fflush(stdout);
    siga.sa_sigaction = *multi_handler;
    siga.sa_flags |= SA_SIGINFO; // get  info
    // change signal action,
    if(sigaction(SIGUSR1, &siga, NULL) != 0) {
        printf("error sigaction()");
        return errno;
    }
    sleep(100);
    cout << "YO";
    fflush(stdout);   
   return 0;
}