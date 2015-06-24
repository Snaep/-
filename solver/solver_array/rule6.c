#include "rules.h"
//Prueft hidden pairs in Spalten
int rule6 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i, j, k, l, m, n;
	int popcnt, cnt, cnt2;
	int *col;

	col = ( int ) calloc ( 0, sud->length*sizeof( int ) );

	for ( i = 0; i < sud->length; i++ )
	{
		for ( j = 0; j < sud->length; j++ )
		{
			if ( sud->grid[j][x][i] == 1 )
			{
				col[i] = 1;
			}
		}
	}

	for ( i = 0; i < sud->length; i++ )
	{
		for ( j = 0; j < sud->length; j++ )
		{
			popcnt = 0;
			if ( col[i] == sud->grid[j][x][i] )
			{
				popcnt++;
			}
		}
		if ( y != j && popcnt == 2 )
		{
			cnt = 0;
			cnt2 = 0;
			for ( k = 0; k < sud->length; k++ )
			{
				if ( sud->grid[y][x][k] == 1 )
				{
					cnt++;
				}

				for ( l = 0; l < sud->length; l++ )
				{
					if ( sud->grid[l][x][k] == 1 )
					{
						cnt2++;
					}
				}
				if ( cnt != 2 || cnt2 != 2 )
				{
					for ( m = 0; m < sud->length; m++ )
					{

						if ( m != k )
						{
							sud->grid[l][x][m] = 0;
							sud->grid[y][x][m] = 0;
						}
					}
				}
			}
		}
	}



	unsigned int i, j;
	SudokuCell candidate, neighbourhood;

	for ( i = 0; i < sud->length; i++ )
	{
		candidate = ( sud->grid[y][x] ) & ( sud->grid[i][x] );
		if ( __popcnt64 ( candidate ) == 2 && i != y )
		{
			if ( ( ( __popcnt64 ( sud->grid[y][x] ) != 2ll ) || ( __popcnt64 ( sud->grid[i][x] ) != 2ll ) ) )
			{
				neighbourhood = 0;
				for ( j = 0; j < sud->length; j++ )
				{
					if ( j != i && j != y ) neighbourhood |= sud->grid[j][x];
				}

				if ( ( candidate & neighbourhood ) == 0 )
				{
					sud->grid[i][x] = candidate;
					sud->grid[y][x] = candidate;
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;
}