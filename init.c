#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>

#define NPROCS 6

int callGetty(int segment_id)
{
    //sleep(1);
    char s[15];
    sprintf(s, "%d", segment_id);
    printf("Im the son %d, %s\n", segment_id, s);
    execlp("/usr/bin/xterm","/usr/bin/xterm", "-e", "./getty", s,(char *)NULL);
    exit(0);
}

int main()
{
    int *shutdown;
    int i;
    int pid;
    
    int pidArr[6];
    int segment_id = shmget(IPC_PRIVATE, sizeof(shutdown), S_IRUSR | S_IWUSR);
    shutdown = shmat(segment_id, NULL, 0);
    *shutdown = 0;

    for(i = 0;i < NPROCS;i++) {
        pid=fork();

        if(pid==0) {
             callGetty(segment_id);
        }
        else{
            pidArr[i] = pid;
        }
    }
    for(i = 0;i < NPROCS;i++) {
        printf("i:%d pid:%d", i, pidArr[i]);
    }

    printf("\nChecking for shutdown\n");
    pid_t r_pid;
    int status;
    while(!*shutdown) {
        sleep(1);
    }
    
    
    printf("Fin\n");
    return 0;
}



