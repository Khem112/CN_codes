#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <semaphore.h>
#include <bits/stdc++.h>
using namespace std;

int main(){
    key_t key = ftok("shmfile",65); 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 
	int *tn = (int*) shmat(shmid,(void*)0,0); 
    *tn = *tn+1;
    int cur_proc = *tn;
    sem_t *psem; 
    int next_proc = *tn+1;
    string cur_str = "/p" + to_string(cur_proc);
    string next_str = "/p" + to_string(next_proc);
    cout << cur_str;
    sem_t *prev = sem_open(cur_str.c_str(), O_CREAT | O_RDWR);
    sem_t *next = sem_open(next_str.c_str(), O_CREAT | O_RDWR, 0660, 0);
    sem_post(prev);
    sleep(1);
    cout << "\nI sent msg to p " << cur_proc;
    sem_wait(prev);
    cout << "\nI'm ready now";
    fflush(stdout);

    string myfifo = "/tmp/myfifo" + to_string(cur_proc);
    int read_fd = open(myfifo.c_str(),O_RDWR);
    char buf[10];
    read(read_fd,buf,sizeof(buf));
    cout << buf ;
    fflush(stdout);
    sem_wait(next);
    cout << "\nprocess " << next_proc << " is arrived";
    fflush(stdout);
    sem_post(next);
    string myfifo2 = "/tmp/myfifo" + to_string(next_proc);
    unlink(myfifo2.c_str());
    mkfifo(myfifo2.c_str(), 0666); 
    int write_fd = open(myfifo2.c_str(),O_CREAT|O_RDWR);
    strcat(buf,"khemraj 2");
    write(write_fd,buf,sizeof(buf));
    while(1){
        
    }
    return 0;
}