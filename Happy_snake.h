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
Screen& Screen::clear(){
	for(int i=2; i < row_limit -2; i++){
		for(int j=2; j < col_limit - 2; j++){
			contents[i *col_limit + j] = ' ';
		}
	}
	return *this;
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
	Snake &move(char dir);
	void Write_to_screen(Screen&);
private:
	std::list<Pos> body;
	char direction= ' ';
};

Snake::Snake(){
	body.push_back(Pos(Pos::row_limit/2,Pos::col_limit/2));
}

int is_opsite(char dir , char origin_dir){
	if( dir == 'w' && origin_dir == 's')
		return 1;
	else if(dir == 'a' && origin_dir == 'd')
		return 1;
	else if(dir == 's' && origin_dir == 'w')
		return 1;
	else if(dir == 'd' && origin_dir == 'a')
		return 1;
	else 
		return 0;
}

Snake& Snake::move(char dir){
	Pos next_head;
	dir = (is_opsite(dir ,direction)) ? direction : dir;
	switch (dir){
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
			next_head = body.front().above();
			break;
	}
	direction = dir;
	body.push_front(next_head);
	body.pop_back();
	return *this;
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

