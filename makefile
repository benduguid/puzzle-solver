all: sudoku
sudoku: sudoku.cpp
	g++ -o sudoku -std=c++17 -Wall -Wextra -pedantic sudoku.cpp
