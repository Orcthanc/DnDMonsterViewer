#include "Monster.h"
#include "DnDConcepts.h"

#include <stdio.h>

DnDMonster* rollDnDMonsterHP( DnDMonster* monster, const char* hp ){
	fprintf( stderr, "%s  %i\n", hp, roll_dice_string( hp ));
	monster->hp = roll_dice_string( hp );
	monster->max_hp = monster->hp;
	
	return monster;
}

DnDAdditionalMonsterInfo** DnDAdditionalMonsterInfoGetLastPointerToNext( DnDMonster* monster ){
	if( !monster->pNext )
		return &monster->pNext;
	DnDAdditionalMonsterInfo* iterator = monster->pNext;
	while( iterator->pNext ){
		iterator = iterator->pNext;
	}
	return &iterator->pNext;
}
