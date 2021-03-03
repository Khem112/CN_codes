#include<bits/stdc++.h>
#include <fstream> 
 #include<stdio.h> 
 #include<unistd.h> 
 #include<fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
using namespace std;

int main(int argc,char *argv[])
{
    sem_t *parent_semaphore = sem_open("/parent4", 1);
    sem_t *child_semaphore = sem_open("/child4", 0);
    int fd=atoi(argv[1]);      //here fd=0 in case dup2 in process ps1.c
    dup2(fd,0);
    string str;
    while(cin){
        if(!cin) return 0;
            sem_wait(child_semaphore);
            getline(cin,str);
            fflush(stdin);
            fflush(stdout);
            if(str!="")
            cout << getpid() << str << "\n";
            fflush(stdout);
            sem_post(parent_semaphore);
            // sleep(1);
            fflush(stdin);
            fflush(stdout);
            str.clear();
    }
}