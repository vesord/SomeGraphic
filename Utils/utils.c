#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void exit_fatal(char * str) {
	write(2, str, strlen(str));
	exit(1);
}