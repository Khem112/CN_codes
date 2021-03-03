#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>

// sem_t *parent_semaphore;
// sem_t *child_semaphore;

int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Child Process could not be created, exiting the program");
        return 0;
    }
    sem_unlink("/parent4");
    sem_unlink("/child4");
    sem_t *parent_semaphore = sem_open("/parent4", O_CREAT | O_RDWR, 0660, 1);
    sem_t *child_semaphore = sem_open("/child4", O_CREAT | O_RDWR, 0660, 0);

    if (pid == 0)
    {
        // write(1, "Executing Child\n", 17);
        while (1)
        {
            sem_wait(parent_semaphore);
            write(1, "Executing Child\n", 17);
            sleep(1);
            sem_post(child_semaphore);
        }
    }
    else
    {
        // write(1, "Executing Parent\n", 18);
        while (1)
        {
            sem_wait(child_semaphore);
            write(1, "Executing Parent\n", 18);
            sleep(1);
            sem_post(parent_semaphore);
        }
    }
    sem_close(parent_semaphore);
    sem_close(child_semaphore);
}