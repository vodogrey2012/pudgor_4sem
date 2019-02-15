#include "dictionary.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct word word = { "" , 0 , NULL};

void dictionary_addword( char* wr)
{
    struct word* cur_word = &word;    
    
    do
    {
        if( !strcmp( cur_word->word , wr))
        {
            ( cur_word->index)++;
            return;
        }
    }
    while( ( cur_word->next_word) && ( cur_word = cur_word->next_word));

    cur_word->next_word = ( struct word*)calloc( 1 , sizeof( struct word));
    cur_word = cur_word->next_word;
    cur_word->word = ( char*)calloc( (strlen( wr) + 1) , sizeof( char));
    sprintf( cur_word->word , "%s" , wr);
    cur_word->index = 1;
    cur_word->next_word = NULL;
}


void dictionary_print()
{
    if( strlen( (word.next_word)->word) == 0)
        return;

    struct word* cur_word = &word;
    do
    {
        cur_word = cur_word->next_word;
        printf("%s \t %d \n" , cur_word->word , cur_word->index);
    }
    while( cur_word->next_word != NULL);
}

