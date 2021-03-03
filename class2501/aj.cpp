#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
using namespace std;
sem_t *x,*y;
void parent(){
    sem_wait(x);
    write(1, "Executing Parent\n", 18);
    sleep(1);
    sem_post(y);
}
void child(){
    sem_wait(y);
    write(1, "Executing Child\n", 17);   
    sleep(1);
    sem_post(x);
}
int main() {
   int pid;
   x = sem_open("/parent4", O_CREAT | O_RDWR, 0660, 1);
   y = sem_open("/child4", O_CREAT | O_RDWR, 0660, 0);
   
   pid = fork();

    if (pid == 0)
    {   

        for(int i=0;i<3;i++) child();
    }
    else
    {
        for(int i=0;i<3;i++) parent();

    }
   return 0;
}