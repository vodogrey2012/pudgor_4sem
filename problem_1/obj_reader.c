#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#include "reader.h"

#define ADDRESS struct reader* p = (struct reader*)( t + 1)

struct reader
{
    FILE* fd;
};


int reader_getword( struct reader_fn* t , char* word)
{
    ADDRESS;

    char c = 0; 
    while( !isalpha( c))
    {
        c = fgetc( p->fd);
        if( c == EOF)
            return 0;
    };

    
    int i = 0;
    for( i = 0 ; isalpha( c) ; i++)
    {
        word[i] = c;
        c = fgetc( p->fd);   
    }
    word[i] = 0;
    return 1;
}


void reader_destroy( struct reader_fn* t)
{
    ADDRESS;
    if( p->fd != 0)
        fclose( p->fd);
    return;
}


struct reader_fn* reader_create( char* file , int mode)
{
    struct reader_fn* t = (struct reader_fn*)calloc( sizeof( struct reader_fn) + sizeof( struct reader) , 1);
    t->getword = &reader_getword;
    t->destroy = &reader_destroy;

    ADDRESS;    

    if( p->fd != 0)
        fclose( p->fd);

    p->fd = mode > 0
          ? fopen( file , "r+")
          : stdin;
    if( p->fd == 0)
    {
        perror(file);
        exit(1);
    }
    return t;
}


