#ifndef RULES_H
#define RULES_H

#include "sudoku.h"

typedef int( *RULE )( struct Sudoku* sud, int x, int y );

int rule0( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule1( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule2( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule3( struct Sudoku* sud, unsigned int x, unsigned int y );

#endif