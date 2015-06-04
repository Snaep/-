#ifndef SUDOKU_H
#define SUDOKU_H

#include "defaults.h"

//fix!
//do not change.
#define CELL_POSSIBLE 1
#define CELL_IMPOSSIBLE 0

#define CONTAINS_ROW 0
#define CONTAINS_COL 1
#define CONTAINS_BOX 2

#define SUDOKUERROR_FILE (-1)
#define SUDOKUERROR_GRIDSIZE (-2)
#define SUDOKUERROR_PARSER (-3)

typedef unsigned long long SudokuCell;

struct Sudoku {
	SudokuCell** grid;
	int** cellvalue;

	unsigned int length;
	unsigned int length_of_box;

	//64Bit Contains Bitmaske
	//bis zu 49*49 sudoku
	//Bitwerte:
	//1: Zahl ist enthalten
	//0: Zahl ist nicht enthalten
	unsigned long long* contains[3]; 

	//funktion zum setzen einer Zelle
	//wird vom Solver gesetzt
	//abhängig vom parallelisierungsmode
	void( *pSetCell )( struct Sudoku* sudoku, unsigned int x, unsigned int y, unsigned int value );
};

//liest eine datei ein und erstellt entsprechende sudoku instanz
//Nach jedem Zellwert muss ein delimiter stehen
//Leere Zellen können als '0' oder '' dargestellt werden.
//Besipiel:
//d: delimiter
//0: leere Zelle
//\n: Zeilenumbruch
//0d1d\n
//1d2d\n
int Sudoku_ParseFile( struct Sudoku* dest, const wchar_t* file, const wchar_t delimiter );

//setzt eine Zelle im Sudoku auf den angegeben Wert
//x,y: koordinate der zu setzenden Zelle
//value: wert die die Zelle enthalten soll
//ist value = 0 werden keine Änderungen vorgenommen
void Sudoku_SetCell( struct Sudoku* sud, unsigned int x, unsigned int y, unsigned int value );

//stellt das Sudoku auf der Konsole dar
void Sudoku_Print( struct Sudoku* sud );

//prüft ob das Sudoku gültig ist
//0: gültig
//-1: nicht gültig
int Sudoku_Validate( struct Sudoku* sud );

#endif