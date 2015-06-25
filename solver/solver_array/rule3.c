#include "rules.h"

//naked pair row
int rule3( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i, j, changed;
	unsigned int k;

	k = 0;
	for( i = 0; i < sud->length; i++ ) {
		if( sud->grid[y][x][i] == 1 ) k++;
	}
	if( k == 2 ) return 0;


	for( i = 0; i < sud->length; i++ ) {
		if( i == x ) continue;

		for( j = 0; j < sud->length; j++ ) {
			k = 1;
			if( sud->grid[y][i][j] != sud->grid[y][x][j] ) {
				k = 0;
				break;
			}
		}

		if( k == 0 ) continue;

		changed = 0;
		for( j = 0; j < sud->length; j++ ) {
			if( j != i && j != x ) {
				for( k = 0; k < sud->length; k++ ) {

				}
			}
		}


		if( (sud->grid[y][i] ^ sud->grid[y][x]) == 0 ) {
			changed = 0;
			for( j = 0; j < sud->length; j++ ) {
				if( j != i && j != x ) {
					changed |= ( sud->grid[y][j] & sud->grid[y][x] );
					sud->grid[y][j] &= ( ~( sud->grid[y][x] ) );
				}
			}

			return changed;
		}
	}

	return 0;
}
