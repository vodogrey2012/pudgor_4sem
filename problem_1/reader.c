#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "reader.h"

extern FILE* stdin;

FILE* fd;

void reader( char* file , int a)
{
    fd = a > 0
          ? fopen( file , "r+")
          : stdin;
    if( fd == 0)
    {
        perror(file);
        exit(1);
    }
}

int reader_getword( char* word)
{
    char c = 0; 
    while( !isalpha( c))
    {
        c = fgetc( fd);
        if( c == EOF)
            return 0;
    };

    
    int i = 0;
    for( i = 0 ; isalpha( c) ; i++)
    {
        word[i] = c;
        c = fgetc( fd);   
    }
    word[i] = 0;
    return 1;
}
