#ifndef HUMAN
#define HUMAN

#include "control.h"
#include "keypressable.h"

class Human : public Control , public Keypressable
{
public:
    Snake* snake;
    Human(Snake* s);
    ~Human();
    
    void onkey(int key);
};

class Robot:public Control
{
public:
    Snake* snake;
    void onthink();
    Coord distance(Coord rab);
    Robot(Snake*);
};


#endif
