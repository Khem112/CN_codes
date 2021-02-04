#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include<bits/stdc++.h>
int pi1[2],pi2[2],pi3[2],pi4[2];
using namespace std;
bool flag = true;

int parseRequests(char buffer[], char *requests[], char delim)
{
    int count = 0;
    if (buffer[0])
        requests[count++] = &buffer[0];
    for (int i = 0; buffer[i]; ++i)
    {
        if (buffer[i] == delim)
        {
            buffer[i] = 0;
            if (buffer[i + 1])
                requests[count++] = &buffer[i + 1];
        }
    }
    requests[count] = NULL;
    return count;
}

void parent_handler(int signum){
    flag = !flag;
    if(flag){
        cout << getpid()+4 << " will receive.. \n";
        killpg(getpid()+2,SIGSTOP);
        killpg(getpid()+4,SIGCONT);
    }
    else{
        cout << getpid()+2 << " will receive.. \n";
        killpg(getpid()+4,SIGSTOP);
        killpg(getpid()+2,SIGCONT);
    }
    
}

int main(){
    if (pipe(pi1) < 0) 
		exit(1); 
    if (pipe(pi2) < 0) 
		exit(1); 
    if (pipe(pi3) < 0) 
		exit(1); 
    if (pipe(pi4) < 0) 
		exit(1); 

        int pid = fork();
        if(pid > 0){
            pid = fork();
            if(pid > 0){
                pid = fork();
                if(pid > 0){
                    pid = fork();
                    if(pid > 0){
                        //parent
                        sleep(2);
                        signal(SIGUSR1,parent_handler);
                        char buffer[1024];
                        char *requests[256];
                        unlink("/tmp/fifo1");
                        unlink("/tmp/fifo2");

                        mkfifo("/tmp/fifo1",0666);
                        mkfifo("/tmp/fifo2",0666);
                        
                        int fd1 = open("/tmp/fifo1", O_RDWR);
                        int fd2 = open("/tmp/fifo2", O_RDWR);
                        cout << "Prent pid " << getpid() << "\n";
                        killpg(getpid()+2,SIGSTOP);
                        killpg(getpid()+4,SIGSTOP);
                        cout << "Pole activated..\n";
                        pollfd fds[2];
                        fds[0] = {fd1, POLL_IN, 0};
                        fds[1] = {fd2, POLL_IN, 0};
                        while (1)
                        {
                            int polls = poll(fds, 2, 500);
                            if (polls > 0)
                            {
                                for (int i = 0; i < 2; i++)
                                {
                                    if (fds[i].revents)
                                    {
                                        int bR = read(fds[i].fd, buffer, 1024);
                                        buffer[bR] = 0;
                                        int rCount = parseRequests(buffer, requests, '\n');
                                        for (int j = 0; j < rCount; ++j)
                                        {
                                            char str[25];
                                            strcat(str,"Client says ");
                                            strcat(str,requests[i]);
                                            cout << str << endl;
                                            fflush(stdout);
                                            if(flag){
                                                write(pi1[1],str,25);
                                                fflush(stdin);
                                                write(pi2[1],str,25);
                                                fflush(stdin);
                                            }
                                            else{
                                                write(pi3[1],str,25);
                                                fflush(stdin);
                                                write(pi4[1],str,25);
                                                fflush(stdin);
                                            }
                                            cout << "done" ;
                                            fflush(stdout);
                                            memset(str,0,25);
                                        }
                                        fds[i].revents = 0;
                                    }
                                }
                            }
                        }  
                    }
                    else{
                        //s1
                        setpgid(getpid(), 4+getppid());
                        cout << "gid of s'1 " << getpgid(getpid()) << "\n";
                        char str[25];
                        while(1){
                            read(pi4[0],str,25);
                            cout << "(from s1) " << str << "\n";
                            fflush(stdout);
                        }
                    }
                }
                else{
                    //s2
                    setpgid(getpid(), 4+getppid());
                    cout << "gid of s'2 " << getpgid(getpid()) << "\n";
                    char str[25];
                    while(1){
                        read(pi3[0],str,25);
                        cout << "(from s2) " << str << "\n";  
                        fflush(stdout);
                    }
                }
            }
            else{
                //a
                setpgid(getpid(), 2+getppid());
                cout << "gid of a " << getpgid(getpid()) << "\n";
                char str[25];
                        while(1){
                            read(pi2[0],str,25);
                            cout << "(from a) " << str << "\n";
                            fflush(stdout);
                        }
                }
        }
        else{
            //b
            setpgid(getpid(), 2+getppid());
            cout << "gid of b " << getpgid(getpid()) << "\n";
            char str[25];
                        while(1){
                            read(pi1[0],str,25);
                            cout << "(from b) " << str << "\n";
                            fflush(stdout);
                        }
        }
    return 0;

}