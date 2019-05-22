#include <sys/time.h>
#include <utility>
#include <iostream> 
#include <poll.h>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <functional>

using namespace std::placeholders;
#include "view.h"

View* View::instance;
View* View::get()
{
	if (instance == 0)
		instance = new View;
	return instance;
}
void onwinch(int sig)
{
	View::get()->draw();
}
void View::cls()
{
	printf("\e[H\e[J");
}
void bye (int go)
{
	//printf("\e[H\e[J");
	View* v = View::get();
	delete v;
	exit(0);
}
void byeSEGV (int go)
{
	//printf("\e[H\e[J");
	View* v = View::get();
	delete v;
	exit(0);
}
void byeINT (int go)
{
	//printf("\e[H\e[J");
	View* v = View::get();
	delete v;
	exit(0);
}
void exitbye()
{
	tcsetattr(0, TCSAFLUSH, &(View::get()->oldtc));
	printf("\e[H\e[J");
}

View::View()
{
	struct termios a;
	tcgetattr(0,&a);
	oldtc = a;
	cfmakeraw(&a);
	tcsetattr(0,TCSAFLUSH,&a);

	setbuf(stdout, NULL);
	signal(SIGWINCH, onwinch);
	instance = this;
	AI_num = 0;

	signal(SIGTERM, bye);
	signal(SIGINT,byeINT);
	signal(SIGSEGV,byeSEGV);
	
}
void View::gotoxy(int x, int y)
{
	printf("\e[%d;%dH",winy-y,x+1);
}

View::~View()
{

	signal(SIGWINCH, SIG_DFL);
	instance = NULL;

	tcsetattr(0,TCSAFLUSH,&oldtc);
}
void View::hline(int x,int y,int len,char c)
{
	gotoxy(x,y);
	for (int i=0;i<len;i++)
		printf("%c",c);

}
void View::vline(int x,int y,int len,char c)
{
	for (int i=y;i<len;i++)
	{
		gotoxy(x,i);
		printf("%c",c);
	}
}
void View::draw()
{
	int i,j;
	struct winsize p;
	ioctl(0,TIOCGWINSZ, &p);
	winy=p.ws_row;
	winx=p.ws_col;

	cls();

	hline(0,0,winx,'_');
	vline(0,0,winy,'|');
	vline(winx-1,0,winy,'|');
	hline(0,winy-1,winx,'_');

	gotoxy(winx/2,winy/2);

	game->rabbit_visitor(std::bind(&View::rabbit_painter, this, _1));
	game->snake_visitor(std::bind(&View::snake_painter, this, _1, _2));

	fflush(stdout);
}
void View::setonkey(Keypressable* x)
{
	keyd=x;
}
void View::run()
{
	int timeout = timer.first;
	while(1)
	{	
		struct pollfd arr[1];
		arr[0].fd = 0;
		arr[0].events = POLLIN;
		
		struct timeval t1;
		gettimeofday(&t1, NULL);

		int n = poll(arr, 1, timeout);
		if (n>0)
		{
			char c;
			read(0, &c, 1);
			if (c =='q')
				break;
			keyd->onkey(c);
		
		}
		for(auto r : AId)
		{
			r->onthink();
		}
		struct timeval t2;
		gettimeofday(&t2, NULL);

		int delta = (t2.tv_sec-t1.tv_sec)*1000+(t2.tv_usec-t1.tv_usec)/1000;
		timeout-=delta;
		if (timeout <=0)
		{
			timer.second();
			timeout = timer.first;
		}
		draw();
	}
	exitbye();
}
void View::rabbit_painter(Coord c)
{
	gotoxy(c.first,c.second);
	putchar('0');
}
void View::snake_painter(Coord c, Direction d)
{
	gotoxy(c.first,c.second);
	const char* s="^v<>*";
	putchar(s[d]);

}
