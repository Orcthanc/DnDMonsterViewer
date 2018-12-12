#ifndef __MONSTER_PARSER_H__
#define __MONSTER_PARSER_H__

#include "Monster.h"

void parseMonster( const char* path, DnDMonster* monster );
void saveMonster( const DnDMonster* monster, const char* path );

#endif
