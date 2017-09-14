FLAGS := --std=c++14
NAME := run
NAMEFILE := source

release : $(NAMEFILE).cpp
	g++ -O3 $(FLAGS) $^ -o $(NAME)
debug : $(NAMEFILE).cpp
	g++ -g $(FLAGS) $^ -o $(NAME)
	gdb $(NAME)
