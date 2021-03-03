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



int main(){    
    int stdin_save;
    stdin_save = dup(STDIN_FILENO); 
    int fd = open("mytext.txt",O_CREAT | O_RDWR);
    char buf[16];
    dup2(fd,STDIN_FILENO);
    close(fd);
    scanf("%s",buf);
    fflush(stdin);
    printf("%s\n",buf);
    fflush(stdout);
    dup2(stdin_save, STDIN_FILENO); 
    close(stdin_save);
    scanf("%s",buf);
    // cin >> buf;
    fflush(stdin);
    printf("%s\n",buf);
    fflush(stdout);
}