#include "Monster.h"

DnDMonster* createDnDMonsterStats( DnDMonster* monster ){
	if( !monster )
		monster = (DnDMonster*) malloc( sizeof( DnDMonster ));
	//TODO
	monster->hp = 10;
	monster->max_hp = 30;
	monster->move_speed = 30;
	monster->ascii_art = "";
	monster->stats = createMonsterStats( NULL );
	monster->pNext = NULL;

	
	return monster;
}
