#include "rules.h"

//prüft ob ein Wert innerhalb einer Box
//nur in der aktuellen Zelle möglich ist
int rule2 ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i;
	SudokuCell box;

	box = 0;
	//Erzeuge Bitvektor aus aktueller Box
	for ( i = 0; i < sud->length_of_box; i++ )
	{
		if ( i != y )
		{
			box |= sud->cellbox[y][x][i];
		}
	}

	//Laufe durch die Kandiaten 
	for ( i = 1; i <= sud->length; i++ )
	{
		//Wenn Kandidat gefunden
		if ( sud->grid[y][x] & ( 1ll << i ) != 0 )
		{
			if ( ( box & ( 1ll << i ) == 0 ) )
			{
				sud->pSetCell ( sud, x, y, i );
				return 1;
			}
		}
	}

	return 0;
}
