#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "dictionary.h"

int main(int argc , char* argv[])
{
    int ret;
    char* word = (char*)calloc( 100 , sizeof( char));
    int i = ( argc != 1)
          ? argc - 1
          : 0;
    do
    {
        reader( argv[i] , i);
        i--;
        while( reader_getword( word))
              dictionary_addword( word);
    }
    while( i > 0);


    free( word);

    dictionary_print();
    return 0;
}
