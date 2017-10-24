#include "Happy_snake.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

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

//TO CUSTMISE
int Snake::is_crash(Pos next_head){
	auto beg = body.begin();
	for(;beg != body.end(); beg++){
		if(next_head.is_equal_to(*beg) )
			return 1;
	}
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
	if(next_head.is_equal_to(snake_food.pos)){
		body.push_front(next_head);
		Generate_food();
	}
	else if(is_crash(next_head)){
		exit(0);
	}
	else{
		body.push_front(next_head);
		body.pop_back();
	}
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
	srand((unsigned)time(NULL));
	int randomnum = rand() % (Pos::row_limit * Pos::col_limit - body.size());
	char tmp_contents[Pos::row_limit*Pos::col_limit]={' '};
	for(auto beg=body.begin(); beg != body.end(); beg++){
		tmp_contents[(*beg).row *Pos::col_limit+(*beg).col]='*';
	}
	for(int i=0; i < Pos::row_limit ; i++){
		for(int j=0; j < Pos::col_limit; j++){
			if(tmp_contents[i * Pos::col_limit + j] != '*'){
				if(randomnum == 0){
					snake_food.pos = Pos(i,j);
				}
				randomnum--;
			}
		}
	}
	//It has a chance of one in five to generate a food with a random value from 50 to 100.
	if(rand() % 5 == 1){
		snake_food.value = 50 + rand() % 50;
		snake_food.type = '?';
	}
}



int main(){
	//TODO add the clock drive to move automatically
	Screen screen;
	Snake snake;
	char dir=' ';
	snake.Write_to_screen(screen);
	screen.display();
	while(1){
		std::cin >> dir;
		screen.clear();
		snake.move(dir).Write_to_screen(screen);
		screen.display();
	}
	return 0;
}
