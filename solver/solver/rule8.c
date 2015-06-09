#include "rules.h"

//Naked pairs box
int rule8 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i, j;
	if ( __popcnt ( sud->grid[y][x] == 2 ) )
	{
		for ( i = 0; i < sud->length; i++ )
		{
			if ( ( sud->grid[y][x] ) ^ ( *sud->cellbox[y][x][i] ) && ( &( sud->grid[y][x] ) ) != sud->cellbox[y][x][i] )
			{
				for ( j = 0; j < sud->length; j++ )
				{
					if ( ( &( sud->grid[y][x] ) ) != sud->cellbox[y][x][j] )
					{
						*sud->cellbox[y][x][j] &= ( ~( sud->grid[y][x] ) );
						return 1;
					}
				}
			}
		}
	}

	return 0;
}
