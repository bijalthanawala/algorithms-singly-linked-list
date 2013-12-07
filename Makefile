all: sll

sll: sll.h sll.c
	g++ -o sll sll.cpp
