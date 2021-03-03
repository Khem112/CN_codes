// Server side C/C++ program to demonstrate Socket programming 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <semaphore.h>
#include <bits/stdc++.h>
using namespace std;
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
	int sfd, nsfd, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char hello[1024]; 
	
	// Creating socket file descriptor 
	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(sfd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	cout << "\nbind to port " << address.sin_port << " successful";
	if (listen(sfd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	cout << "\nListening on port " << address.sin_port << "...\n";
	if ((nsfd = accept(sfd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	cout << "\nAccepting at " <<  nsfd << " \n";
	fflush(stdout);
	int rnsfd1 = dup(nsfd);
	dup2(rnsfd1,0);
	int rnsfd2 = dup(nsfd);
	dup2(rnsfd2,1);
	int pid = fork();
	if(pid == 0)
		execvp("./sd",NULL);
    sleep(1);
	wait(NULL);
	// valread = read( nsfd , buffer, 1024); 
	// printf("%s\n",buffer ); 
	// cin >> hello;
	// fflush(stdin);
	// send(nsfd , hello , strlen(hello) , 0 ); 
	// cout << "Message sent";
	// fflush(stdout);
	return 0; 
} 
