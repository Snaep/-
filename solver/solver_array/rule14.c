#include "rules.h"
int rule14 ( struct Sudoku* sud, unsigned int x, unsigned  int y )
{
	struct Combinator c;
	SudokuCell cellok = { 0 };
	SudokuCell subset = { 0 };
	SudokuCell changed = { 0 };
	SudokuCell temp = { 0 };

	unsigned int i, j, k, l;
	unsigned int index[64] = { 0 };
	unsigned int combination[5] = { 0 };
	unsigned int curcell = BOXINDEX ( sud, x, y );

	j = 0;

	for ( i = 0; i < sud->length; i++ )
	{
		if ( *sud->cellboxvalue[y][x][i] == 0 && i != curcell )
		{
			index[j++] = i;
		}
	}

	if ( j <= 4 ) return 0;

	for ( i = 2; i < 4; i++ )
	{
		Combinator_Initialize ( &c, i, index, j );
		combination[i] = curcell;

		while ( Combinator_GetNext ( &c, combination ) == 0 )
		{

			subset = 0;
			for ( j = 0; j <= i; j++ )
			{
				OR ( subset, combination[j], subset, sud->length );//subset |= combination[j];
				for ( k = j + 1; k <= i; k++ )
				{
					for ( l = 0; l < sud->length; l++ )
					{
						if ( sud->cellbox[y][x][combination[j]][l] == sud->cellbox[y][x][combination[k]][l] )
						{
							cellok[j] = 1;
							cellok[k] = 1; //cellok|= ( ( 1 << j ) | ( 1 << k ) );
							break;
						}
					}
				}
			}
			if ( POPCNT( cellok,sud->length ) != i + 1 ) continue;

			changed = 0;
			for ( j = 0; j < sud->length; j++ )
			{
				
				if (  cellok[j]   == 0 )
				{
					AND ( subset, sud->cellbox[y][x][j], temp, sud->length );
					OR ( changed, temp, changed, sud->length );//changed |= *sud->cellbox[y][x][j] & subset;

					INV ( subset, temp, sud->length );
					AND ( subset, *sud->cellbox[y][x][j], *sud->cellbox[y][x][j], sud->length );//*sud->cellbox[y][x][j] &= ( ~subset );
				}
			}

			return changed != 0;
		}

	}

	return 0;
}