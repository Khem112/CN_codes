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
char received_msg[10];
int err_code;
int pi1[2];
int pi2[2];
int flag = 0;

void handler1(int signum){
    // cout <<"Im called";
    // fflush(stdout);
    int fd1 = open("/tmp/fifo2",O_RDONLY);
    read(fd1,received_msg,10);
    cout << received_msg << "\n";
    fflush(stdout);
    int t = write(pi1[1], received_msg, 10);
    cout << t << "\n";
    fflush(stdout);
    flag = 1;
    killpg(getpid()+2,SIGUSR1);
    killpg(getpid()+4,SIGUSR2);

}

void handler2(int signum){
    // cout <<"Im called";
    // fflush(stdout);
    int fd1 = open("/tmp/fifo2",O_RDONLY);
    read(fd1,received_msg,10);
    cout << received_msg << "\n";
    fflush(stdout);
    int t = write(pi1[1], received_msg, 10);
    cout << t << "\n";
    fflush(stdout);
    flag=0;
    killpg(getpid()+2,SIGUSR2);
    killpg(getpid()+4,SIGUSR1);

}

void g_handler1(int signum){
    cout << getpid() << "I'm paused\n";
    fflush(stdout);
}

void g_handler2(int signum){
    char buf[10];
    fflush(stdout);
    read(pi1[0], buf, 10);
    cout << getpid() << buf << endl;
    fflush(stdout); 
}

int main(){
    if (pipe(pi1) < 0) 
		exit(1); 
    if (pipe(pi2) < 0) 
		exit(1); 
    int pid = fork();
    if(pid > 0){
        pid = fork();
        if(pid > 0){
            pid = fork();
            if(pid > 0){
                pid = fork();
                if(pid > 0){
                    pid = fork();
                    if(pid > 0){
                        //parent
                        int k;
                        unlink("/tmp/fifo2");
                        if((k = mkfifo("/tmp/fifo2",0666)) !=0){
                            cout << "err";
                            cout << k;
                        }
                        signal(SIGUSR1,handler1);
                        signal(SIGUSR2,handler2);
                        cout << "Parent pid " << getpid() << endl;
                        cout << "Parent gid " << getpgid(getpid()) << endl;
                        
                        while(1);
                    }
                    else{
                        //s1
                        signal(SIGUSR1,g_handler2);
                        signal(SIGUSR2,g_handler1);
                        setpgid(getpid(), 4+getppid()) == -1;
                        cout << "gid of s'1 " << getpgid(getpid()) << "\n";
                        while(1);
                    }
                }
                else{
                    //s2
                    signal(SIGUSR1,g_handler2);
                    signal(SIGUSR2,g_handler1);
                    setpgid(getpid(), 4+getppid());
                    cout << "gid of s'2 " << getpgid(getpid()) << "\n";
                    while(1);
                }
            }
            else{
                //a
                signal(SIGUSR1,g_handler2);
                signal(SIGUSR2,g_handler1);
                setpgid(getpid(), 2+getppid());
                cout << "gid of a " << getpgid(getpid()) << "\n";
                while(1);
                }
        }
        else{
            //b
            signal(SIGUSR1,g_handler2);
            signal(SIGUSR2,g_handler1);
            setpgid(getpid(), 2+getppid());
            cout << "gid of b " << getpgid(getpid()) << "\n";
            while(1);
        }
    }
    else{
        //d
        sleep(2);
        cout << "pid of D " << getpid() << "\n";
        sem_unlink("/resp");
        sem_t *getResp = sem_open("/resp", O_CREAT | O_RDWR, 0660, 0);
        bool sent_p1 = 1;
        sleep(2);
        while(1){
            sem_wait(getResp);
            cout << "hi";
            fflush(stdout);
            if(sent_p1){
                cout << ":edsgcfxjdfc";
                kill(getppid(),SIGUSR1);
                sent_p1 = false;
                sleep(1);
            }
            else{
                kill(getppid(),SIGUSR2);
                sent_p1 = true;
                sleep(1);
            }
        }

    }
    return 0;

}