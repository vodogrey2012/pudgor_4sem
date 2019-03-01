#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "dict.h"

int main(int argc , char* argv[])
{
    struct dictionary_fn* p_dict = VAR();
    struct reader_fn* p_read;
    char* word = (char*)calloc( 100 , sizeof( char));
    int i = ( argc != 1)
          ? argc - 1
          : 0;
    do
    {
        p_read = reader_create( argv[i] , i);
        i--;
        while( p_read->getword( p_read , word))
              p_dict->addword( p_dict , word);
    }
    while( i > 0);


    p_dict->print( p_dict);
    p_dict->destroy( p_dict);
    p_read->destroy( p_read);
    free( word);
    
    return 0;
}
