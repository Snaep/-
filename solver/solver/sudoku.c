#include "sudoku.h"
#include "defaults.h"

wchar_t* ReadAllBytes( const wchar_t * file ) {
	FILE *fptr;
	long len;
	wchar_t* retv;

	if( _wfopen_s( &fptr, file, _T( "r" ) ) != 0 ) return NULL;

	fseek( fptr, 0, SEEK_END );
	len = ftell( fptr );

	retv = ( wchar_t* ) malloc( len * sizeof( wchar_t ) + sizeof( wchar_t ) );
	if( retv != NULL ) {
		fseek( fptr, 0, SEEK_SET );
		fread( retv, 1, len, fptr );
		retv[len] = L'\0';
	}

	fclose( fptr );
	return retv;
}
int Sudoku_ParseFile( struct Sudoku* sud, const wchar_t* filepath, const wchar_t delimiter ) {
	TCHAR* file;
	int i, j, rowindex, cellvalue, cellindex, k;
	int retv;

	//read file
	file = ReadAllBytes( filepath );
	if( file == NULL ) return SUDOKUERROR_FILE;

	//clear struct
	memset( sud, 0, sizeof( struct Sudoku ) );
	retv = SUDOKUERROR_PARSER;

	//determine grid size by counting occurences of delimiter in first row
	for( i = 0; file[i] != L'\n'; i++ ) {
		if( file[i] == delimiter ) sud->length++;
	}

	//minimum size of grid is 2x2 (1 2 \n3 4 \n)
	if( sud->length < 2 ) {
		retv = SUDOKUERROR_GRIDSIZE;
		goto CLEANUP;
	}
	sud->length_of_box = ( int ) ( 0.5f + sqrt( sud->length ) );
	if( sud->length_of_box * sud->length_of_box != sud->length ) {
		retv = SUDOKUERROR_GRIDSIZE;
		goto CLEANUP;
	}

	//allocate grid
	sud->grid = ( SudokuCell** ) calloc( sud->length, sizeof( SudokuCell* ) );
	if( sud->grid == NULL ) goto CLEANUP;

	sud->cellvalue = ( int** ) calloc( sud->length, sizeof( int* ) );
	if( sud->cellvalue == NULL ) goto CLEANUP;

	//allocate grid rows
	for( i = 0; i < sud->length; i++ ) {
		sud->grid[i] = ( SudokuCell* ) malloc( sud->length * sizeof( SudokuCell ) );
		if( sud->grid[i] == NULL ) goto CLEANUP;
		//alle werte auf m�glich setzen
		for( j = 0; j < sud->length; j++ ) sud->grid[i] = ( SudokuCell ) -1;
	}

	//allocate contains helper
	for( i = 0; i < 3; i++ ) {
		sud->contains[i] = ( unsigned long long* ) calloc( sud->length, sizeof( unsigned long long ) );
		if( sud->contains[i] == NULL ) goto CLEANUP;
	}

	cellvalue = 0;
	cellindex = 0;
	rowindex = 0;

	//parse grid
	for( i = 0; file[i] != L'\0'; i++ ) {
		//if current tchar is delimiter, finish cell
		if( file[i] == delimiter ) {
			Sudoku_SetCell( sud, cellindex++, rowindex, cellvalue );
			if( cellindex == sud->length ) {
				cellindex = 0;
				//if no. of rows == no. of cols + 1 end parsing
				if( rowindex == sud->length ) break;
			}
			cellvalue = 0;
			//if current tchar is end of line increment rowindex
		} else if( file[i] == L'\n' ) {
			rowindex++;
			//if current tchar is not ctrl tchar, parse as cell content
		} else {
			cellvalue *= 10;
			cellvalue += file[i] - L'0';
		}
	}

	//skip cleanup
	retv = 0;
	goto END;
CLEANUP:
	//free sudoku if allocated
	if( sud != NULL ) {
		//free sudoku grid if allocated
		if( sud->grid != NULL ) {
			for( i = 0; i < sud->length; i++ ) {
				if( sud->grid[i] != NULL ) free( sud->grid[i] );
			}

			free( sud->grid );
		}
		//free cellvalue grid
		if( sud->cellvalue != NULL ) {
			for( i = 0; i < sud->length; i++ ) {
				if( sud->cellvalue[i] != NULL ) free( sud->cellvalue[i] );
			}
			free( sud->cellvalue );
		}
		//free contains grid
		for( i = 0; i < 3; i++ ) {
			if( sud->contains[i] != NULL ) free( sud->contains[i] );
		}

		free( sud );
		sud = NULL;
	}
END:
	//free loaded file
	if( file != NULL ) free( file );
	return retv;
}

int Sudoku_Validate( struct Sudoku* sud ) {
	int i, j;
	int contains_mask = 0;

	//erstelle bitmaske 
	//1 bei jedem m�glichen bit
	for( i = 1; i <= sud->length; i++ ) contains_mask |= ( 1 << i );

	for( i = 0; i < 3; i++ ) {
		for( j = 0; j < sud->length; j++ ) {
			//wenn eine Nachbarschaft eine Zahl nicht enth�lt
			//(=> eine andere Zahl doppelt ist)
			//wird das xor mit der '1-Bitmaske' ein Wert ungleich 0 ergeben
			if( ( sud->contains[i][j] ^ contains_mask ) != 0 ) return -1;
		}
	}
	
	return 0;
}

void Sudoku_SetCell( struct Sudoku* sud, unsigned int x, unsigned int y, unsigned int value ) {
	unsigned int bi, i, j;

	if( value == 0 ) return;

	//store value in grid
	sud->cellvalue[y][x] = value;

	bi = ( y / sud->length_of_box ) * sud->length_of_box + x / sud->length_of_box;

	//set all other values to impossible
	for( i = 1; i <= sud->length; i++ ) sud->grid[y][x] &= ~( 1 << value );

	//store value in contains
	sud->contains[CONTAINS_COL][x] |= ( 1 << value );
	sud->contains[CONTAINS_ROW][y] |= ( 1 << value );
	sud->contains[CONTAINS_BOX][bi] |= ( 1 << value );

	//remove other cells possibility for value
	//col / row
	for( i = 0; i < sud->length; i++ ) {
		sud->grid[y][i] &= ~( 1 << value );
		sud->grid[i][x] &= ~( 1 << value );
	}

	//box
	//determine box start indices
	x -= ( x % sud->length_of_box );
	y -= ( y % sud->length_of_box );

	//invalidate possibility
	for( j = y; j < y + sud->length_of_box; j++ ) {
		for( i = x; i < x + sud->length_of_box; i++ ) {
			sud->grid[j][i] &= ~( 1 << value );
		}
	}
}

void Sudoku_Print( struct Sudoku* sud ) {
	int i, j;

	for( i = 0; i < sud->length; i++ ) {
		if( i && i % sud->length_of_box == 0 ) {
			printf( "--------------------\r\n" );
		}
		for( j = 0; j < sud->length; j++ ) {
			if( j && j % sud->length_of_box == 0 ) printf( "|" );
			if( sud->cellvalue[i][j] != 0 ) printf( " %i", sud->cellvalue[i][j] );
			else printf( "  " );
		}
		printf( "\r\n" );
	}
	printf( "\r\n-----------------------------------\r\n\r\n" );
}
