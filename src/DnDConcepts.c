#include "DnDConcepts.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int rand_inited = 0;

static int16_t roll_die_kind( int8_t number, uint8_t sides ){
	int16_t return_v = 0;
	for( int8_t i = 0; i != number; i += (number > 0) - (number < 0)){
		return_v += ( rand() % sides ) + 1;
	}
	fprintf( stderr, "\t%id%i: %i\n", number, sides, return_v );
	return return_v;
}

int16_t roll_dice( DnDDieRoll* amount ){
	fprintf( stderr, "Rolling dice:\n" );
	if( !rand_inited ){
		srand( time( NULL ));
		rand_inited = 1;
	}

	int16_t result = 0;
	for( uint8_t i = 0; i < amount->different_die; ++i ){
		result += roll_die_kind( amount->num_die[i], amount->die_sides[i] );
	}

	fprintf( stderr, "\tBonus: %i\n\tResult: %i\n", amount->flat_bonus, result + amount->flat_bonus );

	return result + amount->flat_bonus;
}

DnDDieRoll* get_roll_dice_string( const char* string, DnDDieRoll** roll ){
	//Count die
	uint8_t dice_count = 0;
	for( uint8_t i = 0; string[i]; ++i )
		if( string[i] == 'd' )
			dice_count++;

	if( !*roll ){
		(*roll) = calloc( 1, sizeof( DnDDieRoll ) );
	}

	if( (*roll)->num_die ){
		(*roll)->num_die = realloc( (*roll)->num_die, dice_count );
	}
	else{
		(*roll)->num_die = malloc( dice_count );
	}

	if( (*roll)->die_sides ){
		(*roll)->die_sides = realloc( (*roll)->die_sides, dice_count );
	}
	else{
		(*roll)->die_sides = malloc( dice_count );
	}


	(*roll)->different_die = dice_count;
	(*roll)->flat_bonus = 0;

	uint8_t index = 0;

	for( uint8_t i = 0; string[i]; ){

		int16_t num = 0;
		uint16_t num2 = 0;
		int8_t sign = 1;

		if( string[i] == '-' ){
			sign = -1;
			i++;
		}else if( string[i] == '+' ){
			i++;
		}

		while( string[i] >= '0' && string[i] <= '9' ){
			num *= 10;
			num += string[i] - '0';

			i++;
		}

		if( string[i] == 'd' ){
			i++;

			while( string[i] >= '0' && string[i] <= '9' ){
				num2 *= 10;
				num2 += string[i++] - '0';
			}

			(*roll)->num_die[index] = num * sign;
			(*roll)->die_sides[index++] = num2;
		}else {
			(*roll)->flat_bonus += num * sign;
		}
	}

	return (*roll);
}

int16_t roll_dice_string( const char* string ){
	DnDDieRoll roll;
	DnDDieRoll* pRoll = &roll;
	get_roll_dice_string( string, &pRoll );
	int16_t roll2 = roll_dice( &roll );

	destroyDiceRollContents( &roll );

	return roll2;
}

void destroyDiceRollContents( DnDDieRoll* roll ){
	free( roll->die_sides );
	free( roll->num_die );
}
