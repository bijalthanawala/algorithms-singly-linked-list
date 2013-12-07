all: sll

sll: sll.h sll.cpp
	g++ -o sll sll.cpp
