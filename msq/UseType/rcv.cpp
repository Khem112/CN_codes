#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
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
#define PN 2
#define PERMS 0666
int pid_received=0;

struct my_msgbuf {
   long mtype;
   char mtext[200];
};

int pArr[PN];

int chars_to_int(char* s){
    int len = strlen(s);
    int ans=0;
    for(int i=0;i<len;i++){
        ans = 10*ans + (s[i]-'0');
    }
    return ans;
}

void* Reader(void*){
    struct my_msgbuf buf;
    int msqid;
    key_t key;
    int toend=1;

    if ((key = ftok("msgq.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }
   
   if ((msqid = msgget(key, PERMS)) == -1) { /* connect to the queue */
      perror("msgget");
      exit(1);
   }
    for(;;) { /* normally receiving never ends but just to make conclusion 
                /* this program ends wuth string of end */
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        toend = strcmp(buf.mtext,"end");
        if (toend == 0)
        break;
        if(buf.mtype != getpid())
        printf("%d : \"%s\"\n",(int)(buf.mtype), buf.mtext);
        sleep(1);
    }
    printf("message queue: done receiving messages.\n");
    system("rm msgq.txt");
}

int main(void) {
   pthread_t tid1,tid2;
   pthread_create(&tid1,NULL,Reader,NULL);
   pthread_join(tid1,NULL);
   return 0;
}