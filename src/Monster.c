#include "Monster.h"

DnDMonster* createDnDMonsterStats( DnDMonster* monster ){
	if( !monster )
		monster = (DnDMonster*) malloc( sizeof( DnDMonster ));
	//TODO
	monster->hp = 10;
	monster->move_speed = 30;
	monster->ascii_art = "";
	monster->stats = createStats( NULL );
	monster->pNext = NULL;
}
