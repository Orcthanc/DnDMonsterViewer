#include "Monster.h"
#include "DnDConcepts.h"

DnDMonster* createDnDMonsterStats( DnDMonster* monster, const char* hp ){
	if( !monster )
		monster = (DnDMonster*) malloc( sizeof( DnDMonster ));
	//TODO
	monster->hp = roll_dice_string( hp );
	monster->max_hp = monster->hp;
	monster->move_speed = 30;
	monster->ascii_art = "";
	monster->stats = createMonsterStats( NULL );
	monster->pNext = NULL;

	
	return monster;
}
