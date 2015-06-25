#include"rules.h"
int rulesingle ( struct Sudoku* sud, unsigned int x, unsigned int y )
{
	unsigned int i,j,k=0;
	for ( i = 0; i < sud->length; i++ )
	{
		if ( sud->grid[y][x][i] == 1 )
		{
			k++;
			j = i;
		}
	}
	if ( k < 1 )
	{
		return 0;
	}
	else
	{
		sud->pSetCell ( sud, x, y, j );
	}
	return 1;
}