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
#include <sys/uio.h>
#include <bits/stdc++.h>
using namespace std;

int main(){
        char foo[50], bar[50], baz[50];
        struct iovec iov[3];
        ssize_t nr;
        int fd, i,fd1;
        if((fd1 = open("/tmp/fifo1",O_RDONLY))==-1){
            perror ("fifo");
                return 1;
        }
        iov[0].iov_base = foo;
        iov[0].iov_len = sizeof (foo);
        iov[1].iov_base = bar;
        iov[1].iov_len = sizeof (bar);
        iov[2].iov_base = baz;
        iov[2].iov_len = sizeof (baz);

        if((nr = readv(fd1, iov, 3)) == -1) {
              perror ("fifo");
              exit(0);
        }
        
        cout << "nooo" ;
        fflush(stdout);
        for (i = 0; i < 3; i++)
                printf ("%d: %s", i, (char *) iov[i].iov_base);

        if (close (fd1)) {
                perror ("close");
                return 1;
        }
    return 0;
}