#ifndef __STATS_H__
#define __STATS_H__

#include "DnDConcepts.h"

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
DND_Stats* createMonsterStats( DND_Stats* stats );
void deleteMonsterStats( DND_Stats* stats );

#endif
