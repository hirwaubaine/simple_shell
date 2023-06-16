#include "shell.h"

int main(int agc, char **agv, char **environ)
{
	if (agc == 1)
		prompt(agv, environ);
	return (0);
}
