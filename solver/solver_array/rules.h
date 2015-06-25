#ifndef RULES_H
#define RULES_H

#include "sudoku.h"
#include "combinator.h"

typedef int( *RULE )( struct Sudoku* sud, unsigned int x, unsigned int y );

//--------------------------------------------------------------
//add rules here

int rulesingle ( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule0( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule1( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule2( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule3( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule4( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule5( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule6( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule7( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule8( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule9( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule10( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule11( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule12( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule13( struct Sudoku* sud, unsigned int x, unsigned int y );
int rule14( struct Sudoku* sud, unsigned int x, unsigned int y );
void EXOR ( SudokuCell v1, SudokuCell v2, SudokuCell out ,unsigned int n);
void AND ( SudokuCell v1, SudokuCell v2, SudokuCell out, unsigned int n );
void OR ( SudokuCell v1, SudokuCell v2, SudokuCell out, unsigned int n );
void INV ( SudokuCell src, SudokuCell out, unsigned int n );
int POPCNT ( SudokuCell v1,unsigned int n);
//---------------------------------------------------------------
#endif