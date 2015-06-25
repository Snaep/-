#include "rules.h"

void EXOR ( SudokuCell v1, SudokuCell v2, SudokuCell out, unsigned int n )
{
	unsigned int i;
	for ( i = 0; i < n; i++ )
	{
		if ( v1[i] == v2[i] )
		{
			out[i] = 0;
		}
		else
		{
			out[i] = 1;
		}
	}
}
void AND ( SudokuCell v1, SudokuCell v2, SudokuCell out, unsigned int n )
{
	unsigned int i;
	for ( i = 0; i < n; i++ )
	{
		if ( v1[i] == v2[i] && v1[i] == 1 )
		{
			out[i] = 1;
		}
		else
		{
			out[i] = 0;
		}
	}
}
void OR  ( SudokuCell v1, SudokuCell v2, SudokuCell out, unsigned int n )
{
	unsigned int i;

	for ( i = 0; i < n; i++ )
	{
		if ( v1[i] == 1 || v2[i] == 1 )
		{
			out[i] = 1;
		}
		else
		{
			out[i] = 0;
		}
	}
}
void INV( SudokuCell src, SudokuCell out, unsigned int n )
{
	unsigned int i;
	unsigned int *temp;

	temp = ( unsigned int* ) malloc ( sizeof ( unsigned int ) *n );

	for ( i = 0; i < n; i++ )
	{
		if ( src[i] == 1 )
		{
			temp = 0;
		}
		else
		{
			temp[i] = 1;
		}
	}
}
int POPCNT ( SudokuCell src, unsigned int n )
{
	unsigned int i;
	unsigned int cnt=0;
	for ( i = 0; i < n; i++ )
	{
		if ( src[i] == 1 )
		{
			cnt++;
		}
	}
	return cnt;
}