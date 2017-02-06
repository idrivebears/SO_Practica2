#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>

// Commands:
// export: export variables
// echo: echo variables
// exit: 
// shutdown

int main(int argc, char *argv[])
{
    int *shutdown;
	// Recibe seg_id del proceso getty
	if (argc < 2) {
		return 1;
	}

	int seg_id = atoi(argv[1]);
	
	shutdown = shmat(seg_id, NULL, 0);
    int d = *shutdown;
	printf("\n\nS H E L L  A C T I V A T E D\n\n");
	printf("Segment ID received: %d\n", seg_id);
	while(1) {
	    sleep(10);
	    *shutdown = 1;
	    printf("turn off %d, %d\n", *shutdown, d);
	}
	return 0;
}
