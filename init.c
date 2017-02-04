#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NPROCS 4

int proceso(int i)
{
    sleep(1);
    printf("Proceso %d con pid %d\n",i, getpid());
    exit(0);
}

int main()
{
    int i;
    int pid;
    int status;

    for(i = 0;i < NPROCS;i++) {
        pid=fork();

        if(pid==0) {
        	proceso(i);
        }
    }

    for(i=0;i<NPROCS;i++) {
        wait(&status);
    }
    
    printf("Fin\n");
}