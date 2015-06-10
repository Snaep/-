#include "rules.h"

//Hidden Pairs in Boxen
int rule8 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i;

	for ( i = 0; i < sud->length; i++ )
	{
		if ( __popcnt64 ( ( ( sud->grid[y][x] )&( *sud->cellbox[y][x][i] ) ) == 2 && ( &( sud->grid[y][x] ) ) != sud->cellbox[y][x][i] ) )
		{
			if ( __popcnt64 ( sud->grid[y][x] ) != 2 && __popcnt64 ( sud->cellbox[y][x][i] )!=2 )
			{
				*sud->cellbox[y][x][i] = ( ( sud->grid[y][x] )&( *sud->cellbox[y][x][i] ) );
				sud->grid[y][x] = ( ( sud->grid[y][x] )&( *sud->cellbox[y][x][i] ) );

				return 1;

			}
		}
	}
	return 0;
}