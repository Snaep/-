#include "rules.h"

//Naked pairs box
int rule5 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i, j, changed;
	unsigned int k, l, m;

	k = 0;
	for ( i = 0; i < sud->length; i++ )
	{
		for ( m = 0; m < sud->length; m++ )
		{
			if ( ( *sud->cellbox[y][x][i] )[m] == 1 ) k++;
		}
	}
	if ( k == 2 ) return 0;


	for ( i = 0; i < sud->length; i++ )
	{
		if ( sud->cellbox[y][x][i] == &sud->grid[y][x]) continue;

		for ( j = 0; j < sud->length; j++ )
		{
			k = 1;
			for ( m = 0; m < sud->length; m++ )
			{
				if ( ( *sud->cellbox[y][i][j] )[m] != sud->grid[y][x][j] )
				{
					k = 0;
					break;
				}
			}
		}

		if ( k == 0 ) continue;

		changed = 0;
		for ( j = 0; j < sud->length; j++ )
		{
			if ( j != i &&  sud->cellbox[y][x][j] != &sud->grid[y][x] )
			{
				for ( k = 0; k < sud->length; k++ )
				{
					for ( l = 0; l < sud->length; l++ )
					{
						if ( sud->cellbox[y][x][l] == sud->grid[y][j][l] && &sud->grid[y][x] != sud->cellbox[y][x][j] && sud->cellbox[y][x][j]!= sud->cellbox[y][x][i] )
						{
							sud->grid[y][j][l] = 0;
							changed = 1;
						}
					}
				}
			}
		}
	}

	return changed;
}





/*{
	unsigned int i, j, changed;

	if( __popcnt64( sud->grid[y][x] == 2 ) ) {
	for( i = 0; i < sud->length; i++ ) {
	if( ( ( ( sud->grid[y][x] ) ^ ( *sud->cellbox[y][x][i] ) ) == 0 ) && ( &sud->grid[y][x] ) != sud->cellbox[y][x][i] ) {
	changed = 0;
	for( j = 0; j < sud->length; j++ ) {
	changed |= ( ( *sud->cellbox[y][x][j] ) & sud->grid[y][x] );
	*sud->cellbox[y][x][j] &= ( ~( sud->grid[y][x] ) );
	}
	return changed;
	}
	}
	}

	return 0;
	}*/
