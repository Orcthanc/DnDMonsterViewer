#include "Monster.h"
#include "Term.h"
#include "Colors.h"
#include "Parser.h"

#include <stdio.h>
#include <ncurses.h>
#include <signal.h>

int main( int argc, char** argv ){
	DnDMonster* monster = createDnDMonsterStats( NULL );

	initscr();
	start_color();
	use_default_colors();
	curs_set( 0 );

	init_pair( 1, COLOR_WHITE, COLOR_RED );
	init_pair( 2, COLOR_WHITE, COLOR_DARK_GRAY );

	signal( SIGWINCH, handle_winch );

	drawTerm( monster );

	int temp;

	printf( "%i\n", argc );

	JSONObjectDictionary* dict;
	if( argc > 1 )
		dict = parse( argv[1] );
	if( argc > 2 )
		jsonify( argv[2], dict );

	while( (temp = getch()) != 27 ){
		if( temp >= '0' && temp <= '9' )
			monster->hp -= temp - '0';
		drawTerm( monster );
	}

	endwin();
}
