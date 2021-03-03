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
    int fd=atoi(argv[1]);      //here fd=0 in case dup2 in process ps1.c
    dup2(fd,0);
    string str;
    while(cin){
        getline(cin,str);
        fflush(stdin);
        cout << str << "\n";
        fflush(stdout);
        sleep(1);
    }
}