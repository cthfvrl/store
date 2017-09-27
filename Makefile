FLAGS := --std=c++14
NAME := run

release : diff.cpp store.cpp source.cpp
	g++ -O3 $(FLAGS) $^ -o $(NAME)
debug: diff.cpp store.cpp source.cpp
	g++ -g $(FLAGS) $^ -o $(NAME)
	gdb $(NAME)
