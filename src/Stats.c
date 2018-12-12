#include "Stats.h"

DND_Stats* createMonsterStats( DND_Stats* stats ){
	if( !stats )
		stats = (DND_Stats*) malloc( sizeof( DND_Stats ));
#define STAT( A, B ) 							\
	stats->A.stat_type = A;						\
	stats->A.stat_name = #B;
	#include "stats.inl"

	return stats;
}

void deleteMonsterStats( DND_Stats* stats ){
	free( stats );
}

