#include <ctype.h>
#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
using namespace std;

void handler(int signum) {
	cout<<"(from handler) my pid ="<<getpid()<<"  my grp pid ="<<getpgrp()<<endl;
}



int main() {
	int pid = fork();
	if(pid>0){
		signal(SIGUSR1,handler);
        sleep(1);
        cout << "mypid id : " << getpid()<<endl;
		cout<<" And my groupid : " << getpgrp()<<endl;
		killpg(getpgrp(),SIGUSR1);
        sleep(2);
	}
	else{
		    signal (SIGUSR1,handler);
            sleep(1);
			pid_t ppgid=getpgid(getppid());
            cout << "mypid id : " << getpid()<<endl;
		    cout<<" And my groupid : " << getpgrp()<<endl;
            setpgid(getpid(),ppgid);
	        sleep(1);
	}

	return 0;
}