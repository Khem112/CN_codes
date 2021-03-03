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
#define PN 2
#define PERMS 0666
long pid[PN+1];
struct my_msgbuf {
   long mtype;
   char mtext[200];
};

int msqid;
int len;
key_t key;
struct my_msgbuf buf;


void* Reader(void*){
    struct my_msgbuf buf;
    
    for(;;) { /* normally receiving never ends but just to make conclusion 
                /* this program ends wuth string of end */
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        if(buf.mtype == getpid())
            printf("%d : \"%s\"\n",(int)(buf.mtype), buf.mtext);
        else{
                if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
                    perror("msgsnd");
            }
    }
}

void *Writer(void*){
    struct my_msgbuf buf;
    char str[200];
    
    buf.mtype = getpid();
    cout << "OK";
    fflush(stdout);
    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
        int  len = strlen(buf.mtext);
        /* remove newline at end, if it exists */
        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
        for(int i=0;i< PN;i++){
            buf.mtype = pid[i];
            if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
        }
        
    }
}

int main(){
    
    
    if ((key = ftok("msgq.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    
    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    cout << "P2 can access MSQ";
    fflush(stdout);

    sem_t *p2 = sem_open("/p2", O_CREAT | O_RDWR);
    int mypid = getpid();

    buf.mtype = mypid;
    memset(buf.mtext,0,sizeof(buf.mtext));
    strcat(buf.mtext,"");
    len = strlen(buf.mtext)+1;
    for(int i=0;i< PN ; i++){
        if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
    }
    for(int i=0;i< PN ; i++){
        while(1){
            if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
                perror("msgrcv");
                exit(1);
            }
            int f = 0;
            for(int j=0;j<i;j++){
                if(buf.mtype == pid[j]){
                    f =1;
                }
            }
            if( (f==0) && (buf.mtype!=mypid)) {
                pid[i] = buf.mtype;
                cout << "PID " << i << " " << pid[i] << "\n";
                fflush(stdout);
                break;
            }
            else{
                if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
                    perror("msgsnd");
            }
        }
    }
    fflush(stdin);
    sem_post(p2);
    sleep(5);
    sem_wait(p2);
    cout << "Now P2 can send msg too";
        pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,Reader,NULL);
    pthread_create(&tid2,NULL,Writer,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}