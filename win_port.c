#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <stdlib.h>


#define M_MAXSIZE 1024

/* implementation simple de getline() pour windows */
unsigned int getline(char **lineptr, unsigned int *n, FILE *stream)
{
    if(!*lineptr)
    {
	*lineptr = (char*)malloc(M_MAXSIZE);
	*n = M_MAXSIZE;
    }

    if(!fgets(*lineptr,  M_MAXSIZE, stream))
	return (unsigned int)-1;
    
    return strlen(*lineptr);
}


void usleep(unsigned int s)
{
	Sleep(s / 1000);
}


