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
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
using namespace std;

int main() 
{ 

	key_t key = ftok("shmfile",65); 

	int shmid = shmget(key,1024,0666|IPC_CREAT); 

    int pid = fork();
	if(pid>0)
    {
    char *str = (char*) shmat(shmid,(void*)0,0); 

	cout<<"Write Data : "; 
	scanf("%s",str); 

	printf("%s\n",str); 
	
	shmdt(str); 
    wait(NULL);
    }
    else{
        execvp("./p2a",NULL);
    }

	return 0; 
} 
