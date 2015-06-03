#include "defaults.h"
#include "parameterset.h"
#include "solver.h"
#include "sudoku.h"


#ifdef _WIN32
int _wmain( int argc, wchar_t* argv[] ) {
#else
int main( int argc, char* argv[] ) {
	//convert to wchar_t
#endif

	struct ParameterSet params;
	struct Solver solver;
	struct Sudoku sudoku;

	switch( ParameterSet_Parse( &params, argv ) ) {
	case PARAMERROR_NOFILE:
		wprintf_s( L"no sudoku file\n" );
		return EXIT_FAILURE;
	case PARAMERROR_NOSOLVER:
		wprintf_s( L"no solver specified\n" );
		return EXIT_FAILURE;
	case PARAMERROR_NOSTRATEGIES:
		wprintf_s( L"no strategies specified\n" );
		return EXIT_FAILURE;
	case PARAMWARNING_NODELIMITER:
		wprintf_s( L"no delimiter specified\nfallback to ' '\n" );
		break;
	case 0:
#ifdef _DEBUG
		wprintf_s( L"parameter parser succeeded\n" );
#endif
		break;
	}

	switch( Sudoku_ParseFile( &sudoku, params.filepath, params.delimiter ) ) {
	case SUDOKUERROR_FILE:
		wprintf_s( L"unable to open/read file '%s'\n", params.filepath );
		return EXIT_FAILURE;
	case SUDOKUERROR_GRIDSIZE:
		wprintf_s( "invalid gridsize\n" );
		return EXIT_FAILURE;
	case SUDOKUERROR_PARSER:
		wprintf_s( "parsing failed\n" );
		return EXIT_FAILURE;
	case 0:
#ifdef _DEBUG
		wprintf_s( L"sudoku parser succeeded\n" );
#endif
		break;
	}
	

	return 0;
}
