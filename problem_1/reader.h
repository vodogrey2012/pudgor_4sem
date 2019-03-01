#ifndef READER
#define READER

struct reader_fn* reader_create();
struct reader_fn
{
    int( *getword)( struct reader_fn* t , char* word);
    void( *destroy)( struct reader_fn* t);
};

#endif
