#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char * f_name = "password.txt";
	
	

	// Recibe seg_id del proceso ini
	if (argc < 2) {
		return 1;
	}

	int seg_int = atoi(argv[1]);
	printf("Segment ID received: %d\n", seg_int);
	while(1) {
		return 0;
	}
}