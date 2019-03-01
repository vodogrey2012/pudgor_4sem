#ifndef DICT
#define DICT


struct dictionary_fn
{
    void( *addword)( struct dictionary_fn* t , const char* wr);
    void( *print)( struct dictionary_fn* t);
    void( *destroy)( struct dictionary_fn* t);
};


struct dictionary_fn* dictionary_create();
struct dictionary_fn* dictionary_create_tree();



#endif
