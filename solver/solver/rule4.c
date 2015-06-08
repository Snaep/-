#include "rules.h"

//beschreibung
int rule4( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i;
	SudokuCell col;

	col = 0;
	for ( i = 0; i < sud->length; i++ )
	{
		if ( i != x )
		{
			col |= sud->grid[y][i];
		}
	}

	for ( i = 0; i < sud->length; i++ )
	{
		if ( __popcnt ( ( sud->grid[y][x] ) & ( sud->grid[y][i] ) ) == 2 && i != y )
		{
			sud->grid[y][x] = ( ( sud->grid[y][x] ) & ( sud->grid[y][i] ) );
			sud->grid[y][x] = ( ( sud->grid[y][x] ) & ( sud->grid[y][i] ) );
			return 1;
		}
	}
	return 0;
}