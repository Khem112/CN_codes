 #include<stdio.h> 
 #include<unistd.h> 
 #include<fcntl.h> 
 #include<stdlib.h> 
 
 int main() 
 { 
    int fd; 
    char buf[128]; 
    fd=open("mytext.txt",O_RDONLY); 
    read(fd,buf,10); printf("%s",buf); 
    int c=fork(); 
    if(c>0) 
    { 
        read(fd,buf,10);
          //cout<<buf;
        printf("%s",buf); 
    } else { 
         read(fd,buf,10); 
         //cout<<buf; 
         printf("%s",buf); 
    } 
         return 0; 
}