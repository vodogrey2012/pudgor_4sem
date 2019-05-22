#ifndef KEYPRESSABLE
#define KEYPRESSABLE

#include "control.h"

class Keypressable
{
public:
    virtual void onkey( int key) = 0;
    Keypressable() {};
    virtual ~Keypressable() {};
};



#endif
