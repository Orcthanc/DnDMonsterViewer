#include "Monster.h"
#include "TermDrawer.h"
#include "Colors.h"
#include "Parser.h"

#include <stdio.h>
#include <ncurses.h>
#include <signal.h>

int main( int argc, char** argv ){
	DnDMonster* monster = createDnDMonsterStats( NULL );

	initscr();
	cbreak();
	noecho();
	start_color();
	use_default_colors();
	curs_set( 0 );

	init_pair( 1, COLOR_WHITE, COLOR_RED );
	init_pair( 2, COLOR_WHITE, COLOR_DARK_GRAY );

	signal( SIGWINCH, handle_winch );

	drawMonster( monster );

	char buffer[256];
	int temp;

	JSONObjectDictionary* dict;
	if( argc > 1 )
		dict = parse( argv[1] );
	if( argc > 2 )
		jsonify( argv[2], dict );

	int hp_change = 0;
	int hp_change_mult = -1;

	while( (temp = getch()) != 27 ){
		if( temp >= '0' && temp <= '9' )
			hp_change = hp_change * 10 + temp - '0';
		else if( temp == '\n' ){
			monster->hp += hp_change * hp_change_mult;
			hp_change = 0;
			move( LINES - 1, 0 );
			clrtoeol();

		}
		else if( temp == '-' ){
			hp_change_mult *= -1;
			move( LINES - 1, 0 );
			clrtoeol();
		}
		else if( temp == '\b' ){
			hp_change /= 10;
			move( LINES - 1, 0 );
			clrtoeol();
		}

		if( hp_change != 0 ){
			if( hp_change_mult == -1 )
				snprintf( buffer, 256, "Damage: %i", hp_change );
			else
				snprintf( buffer, 256, "Heal: %i", hp_change );
		}

		drawMonster( monster );
		drawCommand( buffer );
	}

	endwin();
}
