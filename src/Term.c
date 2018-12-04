#include "Term.h"
#include "Colors.h"

#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <signal.h>

#define MIN( a, b ) ((a) < (b) ? (a) : (b))
#define MAX( a, b ) ((a) > (b) ? (a) : (b))

uint8_t term_img_outdated = 0;

void handle_winch( int sig ){
	signal( SIGWINCH, SIG_IGN );

	endwin();
	initscr();
	refresh();
	clear();

	term_img_outdated = 1;

	signal( SIGWINCH, handle_winch );
}

void getTermSize( TermSize* t_size ){
/*	#ifdef _WIN32
 *	CONSOLE_SCREEN_BUFFER_INFO csbi;
 *	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
 *
 *	t_size->x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
 *	t_size->y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
 *	#else
 *	struct winsize w;
 *	ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
 *
 *	t_size->x = w.ws_row;
 *	t_size->y = w.ws_col;
 *	#endif
 */

	t_size->x = COLS;
	t_size->y = LINES;
}

void drawTerm( DnDMonster const *monster ){
	TermSize t_size;
	getTermSize( &t_size );

	erase();

	int16_t monster_hp = MAX( 0, monster->hp );

	//HP
	uint8_t text_size = snprintf( NULL, 0, " %i/%i", monster->hp, monster->max_hp );
	char text[text_size];
	snprintf( text, text_size, "%i/%i", monster->hp, monster->max_hp );
	
	uint8_t red_chars = monster_hp * t_size.x / monster->max_hp;
	uint8_t completely_red_chars = MIN( red_chars, (t_size.x - text_size) / 2 );
	
	//Print red part
	attron( COLOR_PAIR( PAIR_WHITE_RED ));
	mvprintw( t_size.y - 2, 0, "%*s%.*s", completely_red_chars, "", MAX( 0, red_chars - completely_red_chars ), text );
	if( red_chars > completely_red_chars + text_size )
		printw( "%*s", red_chars - (completely_red_chars + text_size ), "" );
	attroff( COLOR_PAIR( PAIR_WHITE_RED ));
	
	//Print black part
	attron( COLOR_PAIR( PAIR_WHITE_GRAY ));
	int temp;
	if( red_chars < (temp = (t_size.x - text_size ) / 2 ))
		printw( "%*s", temp - red_chars, "" );
	//Number of written chars
	int num_written = MAX( temp, red_chars );
	printw( "%s%*s", &text[MIN( num_written - temp, text_size - 1)], t_size.x - num_written, "" );
	attroff( COLOR_PAIR( PAIR_WHITE_GRAY ));
}
