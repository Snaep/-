#include "rules.h"

//naked pair row
int rule3 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	/*unsigned int i, j, changed;
	unsigned int k, l;

	k = 0;
	for ( i = 0; i < sud->length; i++ )
	{
	if ( sud->grid[y][x][i] == 1 ) k++;
	}
	if ( k == 2 ) return 0;


	for ( i = 0; i < sud->length; i++ )
	{
	if ( i == x ) continue;

	for ( j = 0; j < sud->length; j++ )
	{
	k = 1;
	if ( sud->grid[y][i][j] != sud->grid[y][x][j] )
	{
	k = 0;
	break;
	}
	}

	if ( k == 0 ) continue;

	changed = 0;
	for ( j = 0; j < sud->length; j++ )
	{
	if ( j != i && j != x )
	{
	for ( k = 0; k < sud->length; k++ )
	{
	for ( l = 0; l < sud->length; l++ )
	{
	if ( sud->grid[y][x][l] == sud->grid[y][j][l]  && x != j && j != i)
	{
	sud->grid[y][j][l] = 0;
	changed = 1;
	}
	}
	}
	}
	}*/
	unsigned int i, j,changed;
	SudokuCell out = { 0 }, temp = { 0 }, temp2 = { 0 };

	if ( POPCNT ( sud->grid[y][x], sud->length ) != 2 )return 0;

	for ( i = 0; i < sud->length; i++ )
	{
		if ( i == x )continue;

		EXOR ( sud->grid[y][i], sud->grid[y][x],out,sud->length);

		if ( POPCNT ( out, sud->length ) )
		{
			changed = 0;
			for ( j = 0; j < sud->length; j++ )
			{
				if ( j != i && j != x )
				{
					AND (sud->grid[y][x], sud->grid[y][j],temp,sud->length );
					OR (temp,temp2,temp,sud->length);

					INV ( sud->grid[y][x], sud->grid[y][j],sud->length );
				}
			}
			return 1;
		}
	}
	return 0;
}
