#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int validate_user(char * user, char * pass)
{
	FILE* fid;
	fpos_t pos;
	int pos_init = 0;

	char in_user[256];
	char in_pass[256];
	char line[512];

	if ((fid = fopen("password.txt","rw+")) == NULL)
	{
		//File failed to open
		fclose(fid);
		return 0;
	}

	// reset position
	if (pos_init)
		fsetpos (fid,&pos);

	// read as many line as you can
	while (!feof(fid))
	{
		if (fscanf(fid,"%s : %s",&in_user, &in_pass))
		{
			if(strcmp(in_user, user) == 0) {
				if(strcmp(in_pass, pass) == 0) {
					return 1;
				}
				printf("Contraseña incorrecta.\n");
			}
		}
		
		fgetpos (fid,&pos); // remember current position
		pos_init = 1; // position has been initialized
	}

	fclose(fid);
	return 0;
}


int main(int argc, char *argv[])
{
	char line[256];
	char user[256];
	char pass[256];
	char seg_id_s[128];
	int seg_id;

	int pid;
	int status;

	// Recibe seg_id del proceso ini
	if (argc < 2) {
		return 1;
	}

	seg_id = atoi(argv[1]);
	
	printf("Segment ID received: %d\n", seg_id);
	sprintf(seg_id_s, "%d", seg_id);

	int login = 0;
	while(1) {
		while(login == 0) {
			printf("Inserte Usuario:> ");
			
			if (fgets(line, sizeof(line), stdin)) {
			    if (sscanf(line, "%s", &user) == 1) {
			    	// recibido
			    }
			}

			printf("Inserte clave:> ");
			if (fgets(line, sizeof(line), stdin)) {
			    if (sscanf(line, "%s", &pass) == 1) {
			    	// recibido
			    }
			}
			printf("Verificando...\n");

			if(validate_user(user,pass) == 1) {
				printf("Login valido.\n", user, pass);
				login = 1;
			}
			else {
				printf("Login no valido. Vuelva a intentar.\n");
				login = 0;
			}
		}
		// Llamar al shell
		
		printf("Calling shell[s_id:%s]...\n", seg_id_s);
		pid = fork();

		if(pid == 0) {
			execlp("./sh","./sh", seg_id_s, (char *)NULL);
		}
		else {
			wait(&status);
		}
		
		//Regresar del shell y volver a pedir informacion login ^
		login = 0;
	}

}