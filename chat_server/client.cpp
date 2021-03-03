#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include<bits/stdc++.h>
#include <fstream> 
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/ipc.h> 
using namespace std; 
sem_t *psem,*csem; 

int main(){
    

    // key_t key = ftok("shmfile",65); 
	// int shmid = shmget(key,1024,0666|IPC_CREAT); 
	int *tn ; //(int*) shmat(shmid,(void*)0,0); 
    // printf("Terminal no. %d",++(*tn));
    char myfifo[80];
    
    char *arr1 = "ex";
    
    int pid = fork();
    if(pid>0){
        sprintf(myfifo,"/tmp/myfifo%d", 1);
        mkfifo(myfifo, 0666); 
        char arr2[80]; 
        int fd = open(myfifo, O_WRONLY); 
        while(1){
            fgets(arr2, 80, stdin); 
            fflush(stdin);
            write(fd, arr2, strlen(arr2)+1);
            if(arr2[0]=='e' && arr2[1]=='x'){
                break;
            }
            sleep(1);
        }
        close(fd);
    }
    else{
        csem = sem_open("/csem",0);
        char *myfifo2 = "/tmp/myfifo2"; 
        mkfifo(myfifo2, 0666); 
        char arr1[100],arr2[80]; 
        int fd1 = open(myfifo2, O_RDONLY); 
        while(1){
            sem_wait(csem);
            read(fd1, arr1, sizeof(arr1));
            printf("<from terminal of client2>%s",arr1);
            fflush(stdout);
        }
        close(fd1);
    }
    
    return 0;
}