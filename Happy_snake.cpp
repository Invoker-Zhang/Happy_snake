#include "Happy_snake.h"
#include <iostream>

//class Pos
//class Screen
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
	//TODO
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
	screen.set(snake_food.pos,snake_food.type);
}

void Snake::Generate_food(){
	//TODO
}



int main(){
	Screen screen;
	Snake snake;
	char dir=' ';
	snake.Write_to_screen(screen);
	screen.display();
	while(std::cin >> dir){
		screen.clear();
		snake.move(dir).Write_to_screen(screen);
		screen.display();
	}
	return 0;
}
