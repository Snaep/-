#include "rules.h"

//Hidden Pairs in Boxen
int rule8( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i, j;
	SudokuCell candidate = { 0 }, neighbourhood = { 0 }, temp = { 0 }, temp2 = { 0 };

	for( i = 0; i < sud->length; i++ ) {

		AND ( sud->grid[y][x], sud->cellbox[y][x][i], candidate, sud->length );//candidate = ( sud->grid[y][x] ) & ( *sud->cellbox[y][x][i] );


		if( ( POPCNT( candidate,sud->length ) == 2 ) && ( &sud->grid[y][x] != sud->cellbox[y][x][i] ) ) {
			if( POPCNT( sud->grid[y][x],sud->length ) != 2 || POPCNT( *sud->cellbox[y][x][i],sud->length ) != 2) {
				neighbourhood = 0;
				for( j = 0; j < sud->length; j++ ) {
					if ( sud->cellbox[y][x][j] != &sud->grid[y][x] && j != i )
					{
						OR ( sud->cellbox[y][x][j], neighbourhood, neighbourhood, sud->length );//neighbourhood |= *sud->cellbox[y][x][j];
					}
				}
				AND ( candidate, neighbourhood, temp, sud->length );
				if( POPCNT(temp,sud->length) == 0 ) {
					INV ( candidate, temp2, sud->length );
					INV ( temp2, *sud->cellbox[y][x][i], sud->length ); //*sud->cellbox[y][x][i] = candidate;
					INV ( temp2, sud->grid[y][x], sud->length );//sud->grid[y][x] = candidate;
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;
}