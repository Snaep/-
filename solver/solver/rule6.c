#include "rules.h"

//beschreibung
int rule6( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	int i, j;
	if( __popcnt( sud->grid[y][x] ) != 2 ) return 0;

	for( i = 0; i < sud->length; i++ ) {
		if( i == x ) continue;
		if( sud->grid[y][i] ^ sud->grid[y][x] == 0 ) {
			for( j = 0; j < sud->length; j++ ) {
				if( j != i && j != x ) sud->grid[y][j] &= stuff;
			}
		}
	}

	return 0;
}