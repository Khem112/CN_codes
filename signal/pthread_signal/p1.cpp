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

pthread_t thread1, thread2;
int sem = 2;
int T = 20;
void handler1(int signum)
{
    cout << "Thread 1: I got signal." << endl;
    fflush(stdout);
    --T;
    // sleep(1);
    pthread_kill(thread2, SIGUSR2);
}
void handler2(int signum)
{
    cout << "Thread 2: I got signal." << endl;
    fflush(stdout);
    --T;
    // sleep(1);
    pthread_kill(thread1, SIGUSR1);
}
void *reader(void *p)
{
    signal(SIGUSR1, handler1);
    --sem;
    while (T);
}
void *writer(void *p)
{
    signal(SIGUSR2, handler2);
    --sem;
    while (T);
}
int main()
{
    int arg;
    pthread_create(&thread1, NULL, reader, (void *)&arg);
    pthread_create(&thread2, NULL, writer, (void *)&arg);

    while (sem)
        ;
    pthread_kill(thread1, SIGUSR1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}