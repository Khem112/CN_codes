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
key_t key;
int *proc_cnt;
sem_t *parent_sem;

int main(){
    key = ftok("shmfile",65); 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 
	proc_cnt = (int*) shmat(shmid,(void*)0,0); 
    *proc_cnt = *proc_cnt+1;
    int cur_proc = *proc_cnt;
    cout << "Hello i'm p" << proc_cnt; 
    fflush(stdout);
    char cur_str[20];
    cout << "rfdgcbf";
    fflush(stdout);
    memset(cur_str,0,20);
    strcat(cur_str,"/parent_sem");
    parent_sem = sem_open(cur_str, O_CREAT | O_RDWR);
    sem_post(parent_sem);
    sleep(1);
    sem_wait(parent_sem);
    cout << "\nI'm connected";
    fflush(stdout);
    char cur_fifo[20];
    memset(cur_fifo,0,20);
    strcat(cur_fifo,"/tmp/myfifo1");
    int fd = open(cur_fifo,O_RDWR);
    char buf[100];
    read(fd,buf,sizeof(buf));
    cout << buf ;
    fflush(stdout);
    string myfifo2 = "/tmp/myfifo0" ;
    unlink(myfifo2.c_str());
    mkfifo(myfifo2.c_str(), 0666); 
    int fd2 = open(myfifo2.c_str(),O_CREAT|O_RDWR);
    strcat(buf,"Please work");
    write(fd2,buf,sizeof(buf));
    while(1);
    return 0;
}