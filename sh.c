#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

// Commands:
// export: export variables
// echo: echo variables
// exit: 
// shutdown

int main(int argc, char *argv[])
{
	// Recibe seg_id del proceso getty
	if (argc < 2) {
		return 1;
	}

	int seg_id = atoi(argv[1]);
	

	printf("\n\nS H E L L  A C T I V A T E D\n\n");
	printf("Segment ID received: %d\n", seg_id);
	return 0;
}