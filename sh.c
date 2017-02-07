#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <sys/shm.h>

// add command execution
// add variable insertion within commands
// 

const char * retrieve_variable(char * var_name)
{
	FILE* fid;
	fpos_t pos;
	int pos_init = 0;

	char var_found[256];
	static char var_val[256];
	char line[512];


	if ((fid = fopen("variables.txt","rw+")) == NULL)
	{
		//File failed to open
		fclose(fid);
		return NULL;
	}

	// reset position
	if (pos_init)
		fsetpos (fid,&pos);

	// read as many line as you can
	while (!feof(fid))
	{
		if (fscanf(fid,"%s : %s",&var_found, &var_val))
		{
			if(strcmp(var_found, var_name) == 0) {
				fclose(fid);
				return var_val;
			}
		}
		
		fgetpos (fid, &pos); // remember current position
		pos_init = 1; // position has been initialized
	}

	fclose(fid);
	return NULL;
}

int insert_variable(char * input)
{
	//$VAR=VAL
	char var_name[256];
	char var_val[256];

	//sscanf(input, "%s%*[^=]%s", var_name, var_val);
	sscanf(input, "%[^=]%*c%s", var_name, var_val);

	FILE *fid;
	fid = fopen("variables.txt", "a");
	
	if(fid == NULL)
		return 0;

	fprintf(fid, "%s : %s\n", var_name, var_val);
	fclose(fid);

	return 1;
}


int main(int argc, char *argv[])
{
    
	// Recibe seg_id del proceso getty
	if (argc < 2) {
		return 1;
	}

	int seg_id = atoi(argv[1]);

	char input[256];
	char command[256];
	const char * var_val;
	char args[256];
	int receivedArgs = 0;
	int pid, status;
	
	// int *shutdown;
	// shutdown = shmat(seg_id, NULL, 0);
    // int d = *shutdown;

	printf("\n\nS H E L L  A C T I V A T E D\n\n");
	printf("Segment ID received: %d\n", seg_id);

	while(1) {
		printf("sh:>");
		if (fgets(input, sizeof(input), stdin)) 
		{
		    if (sscanf(input, "%s %s", &command, &args) == 2) {
		    	//Input received 
		    	receivedArgs = 1;
		    }
		    else if (sscanf(input, "%s", &command) == 1) {
		    	receivedArgs = 0;
		    }
		    else {
		    	printf("Invalid input.\n");
		    	receivedArgs = 0;
		    	continue;
		    }
		}
		// Check command and execute corresponding action

		if(strcmp("exit", command) == 0) {
			return 0;
		}

		else if(strcmp("shutdown", command) == 0) {
			// Escribir a memoria compartida
			//*shutdown = 1;
	    	//printf("turn off %d, %d\n", *shutdown, d);
		}

		else if(strcmp("export", command) == 0) {
			if(receivedArgs) {
				if(var_val = retrieve_variable(args) != NULL) {
					//Variable exists, update value
				}
				else {
					//Variable doesnt exist, create new entry
					insert_variable(args);
					printf("Variable added.\n");

				}
			}
		}

		else if(strcmp("echo", command) == 0) {
			if(receivedArgs) {
				if(var_val = retrieve_variable(args)) {
					printf("%s=%s\n", args, var_val);
				}
				else {
					printf("Variable not found.\n");
				}
			}
			else
				printf("ERROR: Command arguments expected.\n");
		}
		
		else {
			pid = fork();

			if(pid == 0) {
				if(receivedArgs)
					execlp(command, command, args, (char *)NULL);
				else
					execlp(command, command, (char *)NULL);
			}
			else {
				wait(&status);
			}
		}

		// if command not found, try executing program



	}

	return 0;
}
