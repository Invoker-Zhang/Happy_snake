.PHONY:run
run:Happy_snake
	./Happy_snake
Happy_snake:Happy_snake.cpp Happy_snake.h
	g++ -o Happy_snake Happy_snake.cpp -std=c++11
.PHONY:clean
clean:
	rm Happy_snake
