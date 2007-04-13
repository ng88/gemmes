#include <windows.h>
#include <winbase.h>
#include <stdio.h>

void usleep(unsigned int s)
{
	Sleep(s / 1000);
}


unsigned int getline(char **lineptr, unsigned int *n, FILE *stream)
{
	fputs("getline() not yet implemented\n", stderr);
	return (unsigned int)-1;
}
