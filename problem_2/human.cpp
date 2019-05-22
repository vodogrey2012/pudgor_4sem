#include "stdio.h"
#include "stdlib.h"

#include "human.h"
#include "view.h"

Human::Human(Snake* s): snake(s)
{
    View::get()->setonkey(this);
}

Human::~Human() {}

void Human::onkey( int key)
{
//    printf("out -> %c  " , key);
    
    switch( key)
    {
        case 'w' : snake->set_direction(UP);      break;
        case 's' : snake->set_direction(DOWN);    break;
        case 'a' : snake->set_direction(LEFT);    break;
        case 'd' : snake->set_direction(RIGHT);   break;
    }
}

Coord Robot::distance(Coord rab)
{
   return Coord(rab.first - snake -> body.front().first, rab.second - snake -> body.front().second);
}

void Robot::onthink()
{    
    auto rab = View::get() -> game -> rabbits;
    Coord low = rab.front();
    for(auto i:rab)
    {
        if((distance(low).first*distance(low).first + distance(low).second*distance(low).second) > (distance(i).first*distance(i).first + distance(i).second * distance(i).second))
        {
            low = i;
        }
    }
    if(distance(low).first*distance(low).first > distance(low).second*distance(low).second)
    {
        if(distance(low).first > 0)
            snake -> set_direction(RIGHT);
        else
            snake -> set_direction(LEFT);
    }
    else
    {
        if(distance(low).second > 0)
            snake -> set_direction(UP);
        else
            snake -> set_direction(DOWN);
    }
}

Robot::Robot(Snake* s) : snake(s)
{
    View::get() -> setonAI(this);    
}
