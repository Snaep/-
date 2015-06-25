#include "rules.h"

//prüft ob ein Wert innerhalb einer Box
//nur in der aktuellen Zelle möglich ist
int rule2( struct Sudoku* sud, unsigned int x, unsigned int y ) {
	unsigned int i, j, k;


	//loop through candidates
	for( i = 0; i < sud->length; i++ ) {
		//wenn kandidat gefunden
		if( sud->grid[y][x][i] == 0 ) {
			k = 1;
			//prüfe ob kandidat woanders möglich ist
			for( j = 0; j < sud->length; j++ ) {
				if( sud->cellbox[y][x][j] == &sud->grid[y][x] ) continue;
				if( (*sud->cellbox[y][x][i])[j] == 0 ) {
					k = 0;
					break;
				}
			}

			//wenn kandidat an keiner anderen Stelle in Reihe möglich ist
			//Setze Zellwert
			if( k != 0 ) {
				sud->pSetCell( sud, x, y, i + 1 );
				return 1;
			}
		}
	}


	return 0;
}
