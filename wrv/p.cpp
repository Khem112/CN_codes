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
#include <sys/uio.h>
using namespace std;

int main(){
        struct iovec iov[3];
        ssize_t nr;
        int fd1, i;
        unlink("/tmp/fifo1");
        mkfifo("/tmp/fifo1",0666);
        if((fd1 = open("/tmp/fifo1",O_WRONLY))==-1){
            perror ("fifo");
                return 1;
        }
        cout << "debug" ;
        fflush(stdout);
        // char *buf[] = {
        //         "Khemraj is a great coder.\n",
        //         "Use signal.\n",
        //         "It will be like that only.\n" 
        // };

        char foo[50], bar[50], baz[50];
        memset(foo,0,50);
        memset(bar,0,50);
        memset(baz,0,50);
        strcat(foo,"Khemraj is a great coder.\n");
        strcat(bar,"Khemraj is the best coder.\n");
        strcat(baz,"Khemraj is god level coder.\n");

        iov[0].iov_base = foo;
        iov[0].iov_len = sizeof (foo);
        iov[1].iov_base = bar;
        iov[1].iov_len = sizeof (bar);
        iov[2].iov_base = baz;
        iov[2].iov_len = sizeof (baz);


        // for (i = 0; i < 3; i++) {
        //         iov[i].iov_base = buf[i];
        //         iov[i].iov_len = strlen(buf[i])+1;
        //         cout << iov[i].iov_len << "\n";
        //         fflush(stdout);
        // }
        /* with a single call, write them all out */
        
        nr = writev(fd1, iov, 3);
        if (nr == -1) {
                perror ("writev");
                return 1;
        }
        
    
        printf ("wrote %ld bytes\n", nr);
        fflush(stdout);
        // while(1);
        // str(buf[0]);
        return 0;
}