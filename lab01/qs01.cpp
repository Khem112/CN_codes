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
    int   p[2];
    pipe(p);
    int file_desc = open("mytext.txt",O_CREAT | O_RDONLY); 
    string str;
    pid_t pid = fork();
    dup2(file_desc, 0) ; 
    while(cin){
        if(pid==0){
            while(cin){
                getline(cin,str);
                fflush(stdin);
                cout << pid << str << "\n";
                fflush(stdout);
                sleep(1);
            }
        }
        else{
            while(cin){
                getline(cin,str);
                fflush(stdin);
                cout << pid << str << "\n";
                fflush(stdout);
                sleep(1);
            }
        }
    }
    return 0;
}