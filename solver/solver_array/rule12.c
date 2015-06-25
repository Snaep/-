#include "rules.h"
#include "..\\solver\combinator.h"
//:/
//Naked Subsets rows
int rule12( struct Sudoku* sud, unsigned int x, unsigned  int y ) {

	struct Combinator c;
	SudokuCell cellok = { 0 };
	SudokuCell subset = { 0 };
	SudokuCell changed = { 0 };
	SudokuCell temp = { 0 }, temp_sub = { 0 };

	unsigned int i, j, k,l;
	unsigned int index[64] = { 0 };
	unsigned int combination[5] = { 0 };

	j = 0;

	for ( i = 0; i < sud->length; i++ )
	{
		if ( sud->cellvalue[i][x] == 0 && i != y )
		{
			index[j++] = i;
		}
	}

	if ( j <= 4 ) return 0;

	for ( i = 2; i < 4; i++ )
	{
		Combinator_Initialize ( &c, i, index, j );
		combination[i] = y;

		while ( Combinator_GetNext ( &c, combination ) == 0 )
		{

			subset = 0;
			for ( j = 0; j <= i; j++ )
			{
				OR (subset,combination[j],subset,sud->length); //subset |= combination[j];
				for ( k = j + 1; k <= i; k++ )
				{
					AND ( sud->grid[combination[j]][x], sud->grid[combination[k]][x], temp, sud->length );
					if ( POPCNT(temp,sud->length)>0)
					{
						for ( l = 0; l < sud->length; l++ )
						{
							cellok[l] = 0;
						}
						cellok[j] = 1;
						cellok[k] = 1;
						break;
					}
				}
			}
			if (POPCNT( cellok,sud->length ) != i + 1 ) continue;

			changed = 0;
			for ( j = 0; j < sud->length; j++ )
			{
				if (  cellok[j] != 0 )
				{
					AND ( sud->grid[j][x],subset,temp_sub,sud->length);
					OR ( changed, temp,changed,sud->length);

					INV (subset,subset,sud->length );

					AND ( sud->grid[j][x], subset, sud->grid[j][x] ,sud->length);	//sud->grid[j][x] &= ( ~subset );
				}
			}

			return 1;
		}

	}

	return 0;
}
