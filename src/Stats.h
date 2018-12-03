#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef enum {
	#define STAT( A, B ) A,
	#include "stats.inl"
} DND_stat_names;

typedef struct DND_Stat {
	DND_stat_names stat_type;
	const char* stat_name;
	uint8_t ability_score_base;
	int8_t ability_score_bonus;
	int8_t ability_score_mod;

} DND_Stat;

typedef struct {
#define STAT( A, B )							\
	DND_Stat A;
	#include "stats.inl"
} DND_Stats;

/*		if stats == nullptr create new DND_Stats*
 *		Fills the new/passed pointer with values
 *		returns the new/passed pointer
 */
DND_Stats* createStats( DND_Stats* stats ){
	if( !stats )
		stats = (DND_Stats*) malloc( sizeof( DND_Stats ));
#define STAT( A, B ) 							\
	stats->A.stat_type = DND_stat_names::A;		\
	stats->A.stat_name = #B;
	#include "stats.inl"

	return stats;
}

void deleteStats( DND_Stats* stats ){
	free( stats );
}
