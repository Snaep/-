#include "defaults.h"

#ifdef _WIN32
int _wmain( int argc, wchar_t* argv[] ) {
#else
int main( int argc, char* argv[] ) {
	//convert to wchar_t
#endif



	return 0;
}