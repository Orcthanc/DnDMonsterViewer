#ifndef __DND_CONCEPT_H__
#define __DND_CONCEPT_H__

#include <stdint.h>

typedef struct {
	uint8_t different_die;
	int8_t* num_die;
	uint8_t* die_sides;
	int16_t flat_bonus;
} DnDDieRoll;

int16_t roll_dice( DnDDieRoll* amount );

int16_t roll_dice_string( const char* string );

DnDDieRoll* get_roll_dice_string( const char* string, DnDDieRoll** roll );

void destroyDiceRollContents( DnDDieRoll* roll );

#endif
