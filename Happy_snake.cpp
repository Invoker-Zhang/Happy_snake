#include "Happy_snake.h"
#include <iostream>



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
