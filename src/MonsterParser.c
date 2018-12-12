#include "MonsterParser.h"
#include "Parser.h"

#include <string.h>
#include <stdio.h>

static const char* dict_key( const JSONObjectDictionary* dict, size_t i ){
	return dict->entries[i]->key;
}

static JSONObject* dict_value( const JSONObjectDictionary* dict, size_t i ){
	return dict->entries[i]->value;
}

static void parse_name( const JSONObject* name, DnDMonster* monster ){
	monster->name = ((JSONObjectString*)name)->string;
}

static void parse_maxhp( const JSONObject* hp, DnDMonster* monster ){
	rollDnDMonsterHP( monster, ((JSONObjectString*)hp)->string );
}

static void parse_move_speed( const JSONObject* speed, DnDMonster* monster ){
	monster->move_speed = atoi( ((JSONObjectString*)speed)->string );
}

static void parse_ascii_art( const JSONObject* ascii, DnDMonster* monster ){
	monster->ascii_art = ((JSONObjectString*)ascii)->string;
}

static void parse_stats( const JSONObject* stats, DnDMonster* monster ){
	JSONObjectDictionary* dict = (JSONObjectDictionary*)stats;
	monster->stats = createMonsterStats( NULL );
	for( size_t i = 0; i < dict->size; i++ ){
	#define STAT( A, B ) if( !strcmp( #A, dict_key( dict, i ))){				\
		monster->stats->A.ability_score_base =									\
				atoi( ((JSONObjectString*)dict_value( dict, i ))->string );		\
																				\
		monster->stats->A.ability_score_mod =									\
				monster->stats->A.ability_score_base / 2;						\
																				\
		monster->stats->A.ability_score_mod -= 5;								\
		}
		#include "stats.inl"
	}
}

static DnDAttackDamage* parse_damage( const char* dmg_string, DnDAttackDamage** damage ){
	if( !*damage )
		*damage = calloc( 1, sizeof( DnDAttackDamage ) );
	get_roll_dice_string( dmg_string, damage );

	return *damage;
}

static void parse_attack( const JSONObject* attack, DnDMonster* monster ){
	JSONObjectDictionary* dict = (JSONObjectDictionary*)attack;

	DnDAdditionalMonsterInfoAttack* attack_struct = calloc( 1, sizeof( DnDAdditionalMonsterInfoAttack ));

	for( size_t i = 0; i < dict->size; i++ ){
		if( !strcmp( "name", dict_key( dict, i ))){
			attack_struct->name = ((JSONObjectString*)dict_value( dict, i ))->string;
		}
		else if( !strcmp( "description", dict_key( dict, i ))){
			attack_struct->description = ((JSONObjectString*)dict_value( dict, i ))->string;
		}
		else if( !strcmp( "damage", dict_key( dict, i ))){
			attack_struct->damage = parse_damage( ((JSONObjectString*)dict_value( dict, i ))->string, &attack_struct->damage );
		}
		else{
			fprintf( stderr,  "WARNING: Found invalid JSON-Entry %s\n", dict_key( dict, i ));
		}
	}

	attack_struct->sType = eDnDAdditionalMonsterInfoTypeAttack;
	attack_struct->pNext = NULL;


	*DnDAdditionalMonsterInfoGetLastPointerToNext( monster ) = (DnDAdditionalMonsterInfo*)attack_struct;
}

static void parse_attacks( const JSONObject* attacks, DnDMonster* monster ){
	JSONObjectDictionary* dict = (JSONObjectDictionary*)attacks;
	for( size_t i = 0; i < dict->size; i++ ){
		parse_attack( dict_value( dict, i ), monster );
	}
}

static void parse_monster( const JSONObjectDictionary* dict, DnDMonster* monster ){
	for( size_t i = 0; i < dict->size; i++ ){
		if( !strcmp( "name", dict_key( dict, i ))){
			parse_name( dict_value( dict, i ), monster );
		}
		else if( !strcmp( "maxhp", dict_key( dict, i ))){
			parse_maxhp( dict_value( dict, i ), monster );
		}
		else if( !strcmp( "move_speed", dict_key( dict, i ))){
			parse_move_speed( dict_value( dict, i ), monster );
		}
		else if( !strcmp( "ascii_art", dict_key( dict, i ))){
			parse_ascii_art( dict_value( dict, i ), monster );
		}
		else if( !strcmp( "stats", dict_key( dict, i ))){
			parse_stats( dict_value( dict, i ), monster );
		}
		else if( !strcmp( "attack", dict_key( dict, i ))){
			parse_attacks( dict_value( dict, i ), monster );
		}
		else{
			fprintf( stderr,  "WARNING: Found invalid JSON-Entry %s\n", dict_key( dict, i ));
		}
	}
}

void parseMonster( const char* path, DnDMonster* monster ){
	JSONObjectDictionary* dict = parse( path );

	if( monster == NULL )
		monster = malloc( sizeof( DnDMonster ));

	for( size_t i = 0; i < dict->size; i++ ){
		if( !strcmp( "monster", dict->entries[i]->key )){
			parse_monster( (JSONObjectDictionary*)dict->entries[i]->value, monster );
		}
		else {
			fprintf( stderr, "WARNING: Found invalid JSON-Entry %s\n", dict->entries[i]->key );
		}
	}
}

void saveMonster( const DnDMonster* monster, const char* path ){

}
