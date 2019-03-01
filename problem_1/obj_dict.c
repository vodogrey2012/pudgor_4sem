#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "obj_dict.h"

#define ADDRESS struct word* p = ( struct word*)( t + 1)


static struct word
{
    char* word;
    unsigned int index;
    struct word* next_word;
};


static void dictionary_addword( struct dictionary_fn* t , const char* wr)
{
    ADDRESS;

    struct word* cur_word = p;

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


static void dictionary_print( struct dictionary_fn* t)
{
    ADDRESS;

    if( (p->next_word == NULL) || ((p->next_word)->index == 0))
        return;

    struct word* cur_word = p;
    do
    {
        cur_word = cur_word->next_word;
        printf("%s \t %d \n" , cur_word->word , cur_word->index);
    }
    while( cur_word->next_word != NULL);
}


static void word_destroy( struct word* word)
{
    if( word->next_word != 0)
        word_destroy( word->next_word);
    else
    {
        free( word->word);
        return;    
    }
    free( word->word);
    free( word->next_word);
    return;
}


static void dictionary_destroy( struct dictionary_fn* t)
{
    ADDRESS;
    word_destroy( p);
}



struct dictionary_fn* dictionary_create()
{
    struct dictionary_fn* p = ( struct dictionary_fn*)calloc( sizeof( struct dictionary_fn) + sizeof( struct word) , 1);
    
    p->addword = &dictionary_addword;
    p->print = &dictionary_print;
    p->destroy = &dictionary_destroy;

    struct word* t = ( struct word*)( p + 1);
    
    t->word = ( char*)calloc(1 , 1);
    t->index = 0;
    t->next_word = NULL;

    return p;
}
















