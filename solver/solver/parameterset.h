#ifndef PARAMETERSET_H
#define PARAMETERSET_H

struct ParameterSet {

	unsigned int strategies;
	unsigned int solver;

	wchar_t filepath[512];

	struct Sudoku* sud;

};

void ParameterSet_Parse( struct ParameterSet** dest, wchar_t** argv );

#endif