#include "solver.h"
#include "rules.h"

//------------------------------------------------
//edit this array to change ruleset !
static const RULE rules[] = {
	&rule0,
	&rule1,
	&rule2,
	&rule3,
	&rule4,
	&rule5,
	&rule6,
	&rule7,
	&rule8
};

//------------------------------------------------

#define NUM_RULES (sizeof(rules) / sizeof(RULE))


int Solver_Initialize( struct Solver* solver, struct Sudoku* sudoku, int strategies, int mode ) {
	int i, j;

	solver->sudoku = sudoku;

	solver->ctStrategies = __popcnt( strategies );
	solver->rules = ( RULE* ) malloc( sizeof( RULE ) * solver->ctStrategies );
	if( solver->rules == NULL ) return -1;

	j = 0;
	for( i = 0; i < NUM_RULES; i++ ) {
		if( strategies & ( 1 << i ) ) solver->rules[j++] = rules[i];
	}

	solver->mode = mode;
	switch( mode ) {
	case SM_SEQ:
		sudoku->pSetCell = &Sudoku_SetCell;
		break;
	}

	return 0;
}


int SolveSeq( struct Solver* solver ) {
	int change;
	unsigned int y, x;
	unsigned int i;
	unsigned int sc;


	do {
		change = 0;
		sc = 0;

		for( i = 0; i < solver->ctStrategies; i++ )//Loop trought rules
		{
			for( x = 0; x < solver->sudoku->length; x++ )//loop trought x positions
			{
				for( y = 0; y < solver->sudoku->length; y++ ) //Loop trought y positions
				{
					if( solver->sudoku->cellvalue[y][x] != 0 ) continue;
					if( ( change = solver->rules[i]( solver->sudoku, x, y ) ) != 0 ) {
						x = ( unsigned int ) -1;
#ifndef _PRINTGRIDLOOP
			wprintf_s( L"_DEBUG: gridloop\nchanged by rule%i\r\n", i );
			Sudoku_Print( solver->sudoku );
#endif
			            i = 0;
						break;
					}
				}

			}
		}
	} while( change != 0 );

	return 0;
}
int SolvePar( struct Solver* solver ) {
	return -1;
}

int Solver_Solve( struct Solver* solver ) {
	switch( solver->mode ) {
	case SM_SEQ:
		return SolveSeq( solver );
	case SM_PCELL:
		return SolvePar( solver );
	}
	return -1;
}
