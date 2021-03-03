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
    char buf[100];
    strcat(buf,"I love device drivers");
    key_t key = ftok("shmfile",65); 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 
	int *tn = (int*) shmat(shmid,(void*)0,0); 
    *tn = 0;
    sem_t *psem; 
    int cur_proc = *tn;
    int next_proc = *tn+1;
    char my_fifo[20];
    memset(my_fifo,0,20);
    strcat(my_fifo,"/parent_sem");
    cout << "\n" << str;
    fflush(stdout);
    sem_unlink(my_fifo);
    sem_t *parent_sem = sem_open(my_fifo, O_CREAT | O_RDWR, 0660, 0);
    sem_wait(parent_sem);
    cout << "p2 activate";
    sem_post(parent_sem);
    string myfifo = "/tmp/myfifo1";
    unlink(myfifo.c_str());
    mkfifo(myfifo.c_str(), 0666); 
    int write_fd = open(myfifo.c_str(),O_CREAT|O_RDWR);
    write(write_fd,buf,sizeof(buf));
    string myfifo2 = "/tmp/myfifo0" ;
    int fd = open(myfifo2.c_str(),O_RDWR);
    read(fd,buf,sizeof(buf));
    cout << buf ;
    fflush(stdout);
    while(1);
    return 0;
}