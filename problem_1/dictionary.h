#ifndef DICTIONARY
#define DICTIONARY

struct word
{
    char* word;
    unsigned int index;
    struct word* next_word;
};

void dictionary_addword( char* word);
void dictionary_print();
void dictionary_free();

#endif
