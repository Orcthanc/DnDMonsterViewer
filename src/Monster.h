#ifndef __DND_MONSTER_H__
#define __DND_MONSTER_H__

#include <stdint.h>
#include "Stats.h"

typedef enum DnDAdditionalMonsterInfoType {
	eDnDAdditionalMonsterInfoTypeNone,
	eDnDAdditionalMonsterInfoTypeAttack,
	eDnDAdditionalMonsterInfoTypeSpell,
	eDnDAdditionalMonsterInfoTypeCaster,
} DnDAdditionalMonsterInfoType;

typedef struct DnDAdditionalMonsterInfo {
	DnDAdditionalMonsterInfoType sType;
	struct DnDAdditionalMonsterInfo* pNext;
} DnDAdditionalMonsterInfo;

typedef struct DnDAttackDamage {
	struct DnDAttackDamage* next_roll;
	DnDDieRoll damage;
} DnDAttackDamage;

typedef struct {
	DnDAdditionalMonsterInfoType sType;
	DnDAdditionalMonsterInfo* pNext;
	const char* name;
	const char* description;
	DnDAttackDamage* damage;
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
	char* name;
	int16_t hp;
	uint16_t max_hp;
	uint8_t move_speed;
	char* ascii_art;
	DND_Stats* stats;
	DnDAdditionalMonsterInfo * pNext;
} DnDMonster;

DnDMonster* createDnDMonsterStats( DnDMonster* monster );
void deleteDnDMonsterStats( DnDMonster* monster );

#endif
