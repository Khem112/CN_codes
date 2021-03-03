#include<bits/stdc++.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;


int main()
{
    cout << "hi\n";
        int pid  = fork();
        if(pid==0){
            cout <<  "I'm child1\n" ;
            exit(0);
        }
        else{
            cout << "I'm parent\n";
            wait(NULL);
            cout << "Child1 exited\n";
            pid = fork();
            if(pid == 0){
                cout << "I'm child2\n";
                exit(0);
            }
            else{
                wait(NULL);
                cout << "Child2 exited\n";
            }
        } 
}