#ifndef __HAPPY_SNAKE_H__
#define __HAPPY_SNAKE_H__

#include <iostream>
#include <list>
#include <array>

//class Pos
class Pos{
friend class Screen;
public:
	Pos() = default;
	Pos(unsigned r, unsigned c): row(r), col(c) {}
	static const unsigned row_limit=24;
	static const unsigned col_limit=40;
	void print(){ std::cout << this->row << ':' << this->col; }
	Pos above(){ Pos tp = *this; tp.row = (tp.row + row_limit - 1) % row_limit; return tp; }
	Pos left(){ Pos tp = *this; tp.col = (tp.col + col_limit - 1) % col_limit; return tp; }
	Pos below(){ Pos tp = *this; tp.row = (tp.row + row_limit + 1) % row_limit; return tp; }
	Pos right(){ Pos tp = *this; tp.col = (tp.col + col_limit + 1) % col_limit; return tp; }
private:
	unsigned row=0;
	unsigned col=0;
	int check();
};

int Pos::check(){
	return (row < row_limit && col < col_limit) ? 1 : 0;
}

class Food{
friend class Snake;
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
	Screen& clear();
	void display();
	Screen& set(Pos ,char );
	static const unsigned row_limit = Pos::row_limit + 4;
	static const unsigned col_limit = Pos::col_limit + 4;
private:
	std::array<char ,row_limit * col_limit> contents={{' '}} ;
};

//class Snake
class Snake{
public:
	Snake();
	Snake &move(char dir);
	void Write_to_screen(Screen&);
	void Generate_food();
private:
	std::list<Pos> body;
	char direction= ' ';
	Food snake_food;
};

Snake::Snake(){
	body.push_back(Pos(Pos::row_limit/2,Pos::col_limit/2));
	Generate_food();
}


#endif

