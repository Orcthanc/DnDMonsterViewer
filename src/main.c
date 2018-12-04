#include "Monster.h"
#include "Term.h"
#include "Colors.h"

#include <stdio.h>
#include <ncurses.h>
#include <signal.h>

int main( int argc, char** argv ){
	DnDMonster* monster = createDnDMonsterStats( NULL );

	initscr();
	start_color();

	init_color( COLOR_DARK_GRAY, 100, 100, 100 );

	init_pair( 1, COLOR_WHITE, COLOR_RED );
	init_pair( 2, COLOR_WHITE, COLOR_DARK_GRAY );

	signal( SIGWINCH, handle_winch );

	drawTerm( monster );

	int temp;

	while( (temp = getch()) != 27 ){
		//if( term_img_outdated )
		if( temp >= '0' && temp <= '9' )
			monster->hp -= temp - '0';
		drawTerm( monster );
	}

	endwin();
}
