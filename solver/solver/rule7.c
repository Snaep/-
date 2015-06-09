#include "rules.h"

//naked pair col
int rule7( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i, j;
	if( __popcnt64( sud->grid[y][x] ) != 2 ) return 0;

	for( i = 0; i < sud->length; i++ ) {
		if( i == y ) continue;
		if( (sud->grid[i][x] ^ sud->grid[y][x]) == 0 ) {
			for( j = 0; j < sud->length; j++ ) {
				if( j != i && j != y ) sud->grid[j][x] &= ( ~( sud->grid[y][x] ) );
			}

			return 1;
		}
	}

	return 0;
}
