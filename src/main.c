#include "Monster.h"
#include "Term.h"

#include <stdio.h>

int main( int argc, char** argv ){
	DnDMonster* monster = createDnDMonsterStats( NULL );

	drawTerm( monster );
	getchar();
}
