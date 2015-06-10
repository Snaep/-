#include "rules.h"

//fuk dis
int rule11 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i, j, changed, subset, ctPartners;
	unsigned int partners[4];

	for ( subset = 4; subset >= 3; subset-- )
	{
		if ( __popcnt64 ( sud->grid[y][x] ) != subset ) continue;
		
		ctPartners = 0;
		for ( i = 0; i < sud->length; i++ )
		{
			if ( ( i != y ) && ( *sud->cellbox[y][x][i] & sud->grid[y][x] ) && ( ( ( *sud->cellbox[y][x][i] ) & ( ~sud->grid[y][x] ) ) == 0 ) )
			{
				partners[ctPartners++] = i;
			}
		}

		if ( ctPartners != subset ) continue;

		changed = 0;
		for ( i = 0; i < sud->length; i++ )
		{
			changed |= ( (*sud->cellbox[y][x][i]) & ( ~sud->grid[y][x] ) );
			*sud->cellbox[y][x][i] &= ( ~sud->grid[y][x] );
		}

		return changed;
	}

	return 0;
}