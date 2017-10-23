#ifndef __HAPPY_SNAKE_H__
#define __HAPPY_SNAKE_H__

#include <iostream>
#include <list>
#include <array>

//class Pos
class Pos{
friend class Screen;
public:
	Pos(unsigned r, unsigned c): row(r), col(c) {}
	static const unsigned row_limit=24;
	static const unsigned col_limit=40;
	Pos above(Pos p);
	Pos left(Pos p);
	Pos below(Pos p);
	Pos right(Pos p);
private:
	unsigned row=0;
	unsigned col=0;
	int check();
};

Pos above(Pos p){
	Pos tp = p;
	tp.row--;
	if(!check(tp)
}


int Pos::check(){
	return (row < row_limit && col < col_limit) ? 1 : 0;
}

class Food{
public:
private:
	Pos pos;
	int value=10;
	char type='$';
};

//class Screen
class Screen{
friend class Snake;
public:
	Screen();
	void display();
	Screen& set(Pos ,char );
	static const unsigned row_limit = Pos::row_limit + 4;
	static const unsigned col_limit = Pos::col_limit + 4;
private:
	std::array<char ,row_limit * col_limit> contents={{' '}} ;
};

Screen::Screen(){
	for(int i=0; i < row_limit; i++){
		for(int j=0; j < col_limit;j++){
			if(i >= 2 && i <= row_limit -3 && j >=2 && j<=col_limit -3)
				contents[i*col_limit + j] = {' '};
			else 
				contents[i*col_limit + j] = {'/'};
		}
	}
}
void Screen::display(){
	for(int i=0; i < row_limit; i++){
		for(int j=0; j< col_limit; j++){
			std::cout << contents[i * col_limit + j];
		}
		std::cout << std::endl;
	}
}
Screen& Screen::set(Pos pos,char c){
	contents[(pos.row + 2)*col_limit + pos.col + 2] = c;
	return *this;
}
//class Snake
class Snake{
public:
	Snake();
	Snake &move();
	void Write_to_screen(Screen&);
	char direction();
private:
	std::list<Pos> body;
};

Snake::Snake(){
	body.push_back(Pos(Pos::row_limit/2,Pos::col_limit/2));
}

Snake& Snake::move(){
	Pos next_head;
	switch (direction()){
		case 'w':
			next_head = body.front().above();
			break;
		case 'a':
			next_head = body.front().left();
			break;
		case 's':
			next_head = body.front().below();
			break;
		case 'd':
			next_head = body.front().right();
			break;
		default:
			;
	}
}

void Snake::Write_to_screen(Screen &screen){
	auto beg = body.begin();
	auto end = body.end();
	if(beg!=body.end()){
		screen.set(*beg++,'#');
	}
	for(;beg!=body.end(); beg++){
		screen.set(*beg,'*');
	}
}



#endif

