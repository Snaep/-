#ifndef SUDOKU_H
#define SUDOKU_H

#define CELL_POSSIBLE 1
#define CELL_IMPOSSIBLE 0

#define CONTAINS_ROW 0
#define CONTAINS_COL 1
#define CONTAINS_BOX 2
#define NUM_ELEMENTS 3

struct Sudoku {
	unsigned long long** grid;
	int** cellvalue;

	unsigned long long* contains[3]; //64Bit Contains Bitmaske
};

#endif