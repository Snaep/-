#include "rules.h"
//Prueft hidden pairs in Spalten
int rule3 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i, j;
	unsigned int iTemp;
	SudokuCell col;

	col = 0;
	for ( i = 0; i < sud->length; i++ )
	{
		if ( i != y )
		{
			col |= sud->grid[i][x];
		}
	}

	for ( i = 0; i < sud->length; i++ )
	{
		if ( __popcnt ( ( sud->grid[y][x] ) & ( sud->grid[i][x] ) ) == 2 && i != y )
		{
			iTemp = i;
			sud->grid[i][x] &= ( sud->grid[y][x] ) & ( sud->grid[i][x] );
			sud->grid[y][x] &= ( sud->grid[y][x] ) & ( sud->grid[i][x] );
		}
	}


	return 0;
}
