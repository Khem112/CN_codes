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
    FILE *verdict_file_pointer;
    FILE *expected_output_file_pointer;
    char code_output_text_str[80];
    char expected_output_text_str[80];
    int stdin_save;
    char command[1024];
    char file_name[1024];
    scanf("%s",file_name);
    sprintf(command,"c++ -pthread %s -o out2", file_name);
    int have_compilation_error = system(command);
    if(have_compilation_error>0){
        int verdict_fd = open("verdict.txt",O_CREAT | O_RDWR);
        write(verdict_fd,"Compilation Error\n",18);
        fflush(stdout);
    }
    else{
        char code_output_text_str[80];
        char exected_output_text_str[80];
        int stdin_save;
        stdin_save = dup(STDIN_FILENO); 
        int input_text_fd  = open("in.txt",O_CREAT | O_RDWR);
        dup2(input_text_fd,STDIN_FILENO);
        close(input_text_fd);
        FILE* code_output_file_pointer = popen("./out2","r");
        int code_output_text_fd = fileno(code_output_file_pointer);
        dup2(code_output_text_fd,STDIN_FILENO);
        close(code_output_text_fd);
        expected_output_file_pointer = fopen("out.txt", "r"); 
        while (!feof(expected_output_file_pointer))  
        { 
            fscanf(expected_output_file_pointer,"%s",expected_output_text_str);
            fflush(stdin);
            scanf("%s",code_output_text_str); 
            fflush(stdin);
            if(strcmp(expected_output_text_str,code_output_text_str)){
                verdict_file_pointer = fopen("verdict.txt", "w"); 
                fprintf(verdict_file_pointer,"Wrong Anwer\n");
                fflush(stdout);
                return 0;
            }
        } 
        dup2(stdin_save, STDIN_FILENO); 
        close(stdin_save);
        verdict_file_pointer = fopen("verdict.txt", "w"); 
        fprintf(verdict_file_pointer,"Wow...It's AC\n");
        fflush(stdout);
        exit(0);
    }
    

}