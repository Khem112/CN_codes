// Server side C/C++ program to demonstrate Socket programming 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
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
#define PORT 8080 

void capitalize(char buf[1024]){
    for(int i=0;i<strlen(buf);i++){
        buf[i] = char(buf[i]+('A'-'a'));
    }
}

int main(int argc,char *argv[])
{
    char str[1024];
    while(1){
        memset(str, 0, 1024);
        read(0,str,1024);
        capitalize(str);
        fflush(stdin);
        cout << str;
        fflush(stdout);
    }
    return 0;
}