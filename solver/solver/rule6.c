#include "rules.h"
//Prueft hidden pairs in Spalten
int rule6 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i;

	for ( i = 0; i < sud->length; i++ )
	{
		if ( __popcnt64 ( ( sud->grid[y][x] ) & ( sud->grid[i][x] ) ) == 2 && i != y )
		{
			sud->grid[i][x] = ( ( sud->grid[y][x] ) & ( sud->grid[i][x] ) );
			sud->grid[y][x] = ( ( sud->grid[y][x] ) & ( sud->grid[i][x] ) );
			return 1;
		}
	}
	return 0;
}
