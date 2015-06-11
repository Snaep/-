#include "rules.h"

//Hidden pairs in Reihen
int rule7( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i;

	for( i = 0; i < sud->length; i++ ) {
		if( __popcnt64( ( sud->grid[y][x] ) & ( sud->grid[y][i] ) ) == 2 && i != x ) {
			if( ( ( __popcnt64( sud->grid[y][x] ) != 2ll ) || ( __popcnt64( sud->grid[y][i] != 2ll ) ) ) != 0 ) {
				sud->grid[y][x] = ( ( sud->grid[y][x] ) & ( sud->grid[y][i] ) );
				sud->grid[y][x] = ( ( sud->grid[y][x] ) & ( sud->grid[y][i] ) );
				return 1;
			}
			return 0;
		}
	}
	return 0;
}