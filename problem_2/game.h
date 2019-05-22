#ifndef GAME_H
#define GAME_H

#include <list>
#include <utility>
#include <functional>

class Control;

enum Direction
{
    UP, DOWN, LEFT, RIGHT, BODY
};

    using Coord = std::pair<int,int>;
    using Rabbit = Coord;
    using RabbitPainter = std::function<void(Coord)>;
    using SnakePainter = std::function<void(Coord,Direction)>;

class Snake;

class Game 
{
public:
    void checkalive();
    void rabbit_visitor(RabbitPainter);
    void snake_visitor(SnakePainter);
    void move();
    
    std::list<Snake*> snakes;
    std::list<Rabbit> rabbits;

    void add_snake(Snake* snake);
    Game();
    ~Game();
};

class Snake 
{
public:
    Snake();
    Snake(int a, int b);
    
    std::list<Coord> body;

    void set_direction (Direction d);
    bool alive;
    void move(std::list<Coord> &rabbits);
    Coord next();
    bool find;

    Direction dir;
};

#endif // GAME_H
