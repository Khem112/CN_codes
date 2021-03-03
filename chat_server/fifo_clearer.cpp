#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#define CLIENT_COUNT 2
#define BUFSIZE 1024

int main()
{
    int mainQ;
    char *fifo1 = "/tmp/myfifo1";
    char *fifo2 = "/tmp/myfifo2";
    char *mainFifo = "/tmp/myfifo3";
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);
    mkfifo(mainFifo, 0666);
    unlink(fifo1);
    unlink(fifo2);
    unlink(mainFifo);
}