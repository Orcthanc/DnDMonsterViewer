#ifndef __DND_MONSTER_H__
#define __DND_MONSTER_H__

#include <stdint.h>
#include "Stats.h"

enum DnDAdditionalMonsterInfoType {
	eDnDAdditionalMonsterInfoTypeNone,
	eDnDAdditionalMonsterInfoTypeCaster,
	eDnDAdditionalMonsterInfoTypeSpell,
};

typedef struct DnDAdditionalMonsterInfo {
	DnDAdditionalMonsterInfoType sType;
	DnDAdditionalMonsterInfo* pNext;
} DnDAdditionalMonsterInfo;

typedef struct {
	DnDAdditionalMonsterInfoType sType;
	DnDAdditionalMonsterInfo* pNext;
} DnDAdditionalMonsterInfoAttack;

typedef struct {
	DnDAdditionalMonsterInfoType sType;
	DnDAdditionalMonsterInfo* pNext;

} DnDAdditionalMonsterInfoSpell;

typedef struct {
	DnDAdditionalMonsterInfoType sType;
	DnDAdditionalMonsterInfo* pNext;
	
	DnDAdditionalMonsterInfoSpell* firstSpell;
	uint32_t spell_amount;
} DnDAdditionalMonsterInfoCaster;

typedef struct {
	uint16_t hp;
	uint8_t move_speed;
	char* ascii_art;
	DND_Stats* stats;
	DnDAdditionalMonsterInfo * pNext;
} DnDMonster;

DnDMonster* createDnDMonsterStats( DnDMonster* monster );
void deleteDnDMonsterStats( DnDMonster* monster );

#endif