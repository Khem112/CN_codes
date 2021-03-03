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
int khem=0;
int fd[2];//File descriptor for creating a pipe
char arr1[80],arr2[80]; 
sem_t *psem,*csem; 
char * myfifo1 = "/tmp/myfifo1"; 
char * myfifo2 = "/tmp/myfifo2"; 
int fd_fifo1,fd_fifo2;
//This function continously reads fd[0] for any input data byte
//If available, prints

void *reader(void*)
{
    printf("READER THREAD IS ON\n");
    fflush(stdout);
    int     count = 0;
    sleep(1);
    //Delay in starting the reading from the pipe
    fd_fifo2 = open(myfifo2, O_WRONLY);
    while(1){
        sem_wait(psem);
        char ch[100];
        read(fd[0], arr2, 80); 
        write(fd_fifo2, arr2, sizeof(arr2));
        printf("Arr2 read successfully\n");
        fflush(stdout);
        sem_post(csem); 
    }
}

//This function continously writes Alphabet into fd[1]

void *writer(void*)
{
    char arr1[80],arr2[80]; 
    system("gnome-terminal -- ./out");
    fd_fifo1 = open(myfifo1, O_RDONLY); 
    while(1){
        read(fd_fifo1, arr1, sizeof(arr1));
        if(arr1[0]=='e' && arr1[1]=='x'){
            break;
        } 
        printf("User2: %s\n", arr1); 
        write(fd[1], arr1, 80); 
        sem_post(psem);
        wait(NULL);
    }
    unlink(myfifo1);
}


int main()
{
    sem_unlink("/psem");
    sem_unlink("/csem");
    psem = sem_open("/psem", O_CREAT | O_RDWR, 0660, 0);
    csem = sem_open("/csem", O_CREAT | O_RDWR, 0660, 0);
    mkfifo(myfifo1, 0666); 
    mkfifo(myfifo2, 0666); 
    if (pipe(fd) < 0) 
		exit(1); 
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,writer,NULL);
    pthread_create(&tid2,NULL,reader,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    
}
