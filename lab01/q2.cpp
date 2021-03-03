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

int main()
{
    string str;
    printf("Hello this is process 1\n");
    int fd=open("./mytext.txt",O_RDONLY);
    int h=fork();
    dup2(fd,0);//note we will be loosing standard input in p2
    while(cin){
        if(h==0)
        {
           // dup2(fd,0);//note we will be loosing standard input in p2
            execvp("./p2",NULL);
            sleep(1);
        }
        else
        {
            while(cin){
                    getline(cin,str);
                    fflush(stdin);
                    cout << h << str << "\n";
                    fflush(stdout);
                    sleep(1);
            }
        }
    }
}