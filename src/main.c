#include "Monster.h"
#include <stdio.h>

int main( int argc, char** argv ){
	DnDMonster* monster = createDnDMonsterStats( NULL );
	printf( "%i\n", monster->hp );
}
