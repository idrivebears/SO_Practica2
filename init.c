#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

#define NPROCS 6

int callGetty(int segment_id, int segment_id2, int i)
{
    //sleep(1);
    char s[15];
    sprintf(s, "%d", segment_id);
    char s2[15];
    sprintf(s2, "%d", segment_id2);
    char s3[15];
    sprintf(s3, "%d", i);
    printf("Im the son %d, %s, %s\n", segment_id, s2, s3);
    execl("/usr/bin/xterm","/usr/bin/xterm", "-e", "./getty", s, s2, s3 ,(char *)NULL);
    exit(0);
}

int main()
{
    int *shutdown;
    int i;
    int pid;
    
    int *pidArr;
    int segment_id = shmget(IPC_PRIVATE, sizeof(shutdown), S_IRUSR | S_IWUSR);
    int segment_id2 = shmget(IPC_PRIVATE, sizeof(pidArr), S_IRUSR | S_IWUSR);
    shutdown = shmat(segment_id, NULL, 0);
    *shutdown = 0;
    pidArr = shmat(segment_id2, NULL, 0);
    for(i = 0;i < NPROCS;i++) {
        pid=fork();

        if(pid==0) {
            int c = i;
            callGetty(segment_id, segment_id2, c);
        }
        else{
            pidArr[i] = pid;
        }
    }
    for(i = 0;i < NPROCS;i++) {
        printf("i:%d pid:%d", i, pidArr[i]);
    }

    printf("Checking for shutdown\n");
    pid_t r_pid;
    int status;
    int err;
    while(!*shutdown) {
        sleep(2);
        for(i = 0; i < NPROCS; i++) {
            err = kill(pidArr[i], 0);
            //printf("h %d, %d\n", pidArr[i], err);
            if(err < 0) {
                pid=fork();

                if(pid==0) {
                    int c = i;
                    callGetty(segment_id, segment_id2, c);
                }
            }
        }
        /*for(i = 0; i < NPROCS; i++) {
            r_pid = waitpid(pidArr[i], &status, WNOHANG);

            if((int) r_pid == pid) {
                //callGetty(segment_id);
                printf("Process [%d] closed.\n", pid);
            }
            else {
                //process still running
            }
        }*/
    }
    
    
    printf("Fin\n");
    return 0;
}



