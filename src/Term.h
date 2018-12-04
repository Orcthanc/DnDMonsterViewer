#ifndef __TERM_H__
#define __TERM_H__

#include "Monster.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#endif

typedef struct {
	uint8_t x;
	uint8_t y;
} TermSize;

void getTermSize(TermSize* t_size);

void drawTerm( DnDMonster const *monster );

#endif
