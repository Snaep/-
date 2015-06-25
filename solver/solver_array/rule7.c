#include "rules.h"

//Hidden pairs in Reihen
int rule7( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	{
		unsigned int i, j;
		SudokuCell candidate = { 0 }, neighbourhood = { 0 }, temp = { 0 };

		for ( i = 0; i < sud->length; i++ )
		{
			AND ( sud->grid[y][x], sud->grid[y][i], candidate, sud->length );  //candidate = ( sud->grid[y][x] ) & ( sud->grid[i][x] );
			if ( POPCNT ( candidate, sud->length ) == 2 && i != x )
			{
				if ( ( ( POPCNT ( sud->grid[y][x], sud->length ) != 2 ) || ( POPCNT ( sud->grid[y][i], sud->length ) != 2 ) ) )
				{
					neighbourhood = 0;
					for ( j = 0; j < sud->length; j++ )
					{
						if ( j != i && j != x )
						{
							OR ( neighbourhood, sud->grid[y][j], neighbourhood, sud->length ); //neighbourhood |= sud->grid[j][x];
						}
					}
					AND ( candidate, neighbourhood, temp, sud->length );
					if ( POPCNT ( temp, sud->length ) == 0 )
					{
						INV ( candidate, temp, sud->length );
						INV ( temp, sud->grid[y][i], sud->length );  //sud->grid[i][x] = candidate;

						INV ( temp, sud->grid[y][x], sud->length );//sud->grid[y][x] = candidate;
						return 1;
					}
				}
				return 0;
			}
		}
		return 0;
	}
	
	
	/*unsigned int i, j;
	SudokuCell candidate, neighbourhood;

	for( i = 0; i < sud->length; i++ ) {
		candidate = ( sud->grid[y][x] ) & ( sud->grid[y][i] );
		if( __popcnt64( candidate ) == 2ll && i != x ) {
			if( ( __popcnt64( sud->grid[y][x] ) != 2ll ) || ( __popcnt64( sud->grid[y][i] ) != 2ll ) ) {
				neighbourhood = 0;
				for( j = 0; j < sud->length; j++ ) {
					if( j != i && j != x ) neighbourhood |= sud->grid[y][j];
				}

				if( ( candidate & neighbourhood ) == 0 ) {
					sud->grid[y][i] = candidate;
					sud->grid[y][x] = candidate;
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;*/
}