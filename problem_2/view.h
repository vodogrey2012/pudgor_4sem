#pragma once
#include <utility>
#include <iostream>
#include <termios.h>
#include "keypressable.h"
#include "game.h"
#include "control.h"
#include "human.h"

using namespace std;

class View
{
	int AI_num;
public:
	View();
	~View();
	void draw();
	void run();
	static View* get();
	void cls();
	void setonkey(Keypressable*);
    void setonAI(Robot* R)
    {  
        AId.push_front(R);
    }
	void rabbit_painter(Coord);
	void snake_painter(Coord, Direction);
	void setgame(Game* g)
	{
		game = g;
	}

	using fn_type = std::function<void()>;
		
	void settimer(int ms, fn_type fn)
	{
		timer = std::make_pair(ms, fn);
	}

	int winx, winy;
	std::pair <int,fn_type> timer;
	Game* game;
	struct termios oldtc;
private:
	void gotoxy(int,int);
	void hline(int,int,int,char c='#');
	void vline(int,int,int,char c='#');
	void size(int);

	static View* instance;
	
	Keypressable* keyd;
    list<Robot*> AId;
};
