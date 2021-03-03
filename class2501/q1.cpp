#include<bits/stdc++.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;
 
void print_pid(){
    cout << "my pid is " << getpid() << "\n";
}

int main()
{
    cout << "hi\n";
        int pid  = fork();
        if(pid==0){
            cout <<  "I'm child1\n" ;
            // print_pid();
            pid  = fork();
            // print_pid();
            if(pid==0){
                cout <<  "I'm child2\n" ;
                pid  = fork();
                if(pid==0){
                    cout <<  "I'm child3\n" ;
                    pid  = fork();
                    if(pid==0){
                        cout <<  "I'm child4\n" ;
                    }
                    else{
                        wait(NULL);
                        cout <<  "my child4 is over\n";
                    }
                }
                else{
                    wait(NULL);
                    cout <<  "my child3 is over\n";
                }
            }
            else{
                wait(NULL);
                cout << "my child2 is over\n";
            }
        }
        else{
            wait(NULL);
            cout <<  "my child1 is over\n";
        }
        exit(0);
}