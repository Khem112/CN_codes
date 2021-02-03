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

int main(){
    sem_t *getResp = sem_open("/resp", O_RDWR);
    int fd1 = open("/tmp/fifo2",0666);
    int pid;
    cout << "Press enter to start";
    fflush(stdout);
    cin >> pid;
    char buf[10] = "from c2!!";
    for(;;){
        write(fd1,buf,10);
        cout << "sent";
        fflush(stdout);
        sem_post(getResp); 
        sleep(1);
    }
}