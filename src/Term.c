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

/*	t_size->x = COLS;
 *	t_size->y = LINES;
 */
}

static char determine_char( uint16_t pos, char* string, uint8_t stringsize ){
	if( pos < ( COLS - stringsize ) / 2 || pos > ( COLS - stringsize ) /2 + stringsize - 1 ){
		return ' ';
	}
	else{
		return string[ pos - (COLS - stringsize) / 2 ];
	}
}

static uint8_t set_color( uint16_t pos, uint8_t curr_color, uint16_t hp, uint16_t maxhp ){
	uint8_t color;
	
	if( pos < hp * ( COLS + 1 ) / maxhp )
		color = PAIR_WHITE_RED;
	else
		color = PAIR_WHITE_GRAY;

	if( color == curr_color )
		return curr_color;
	if( curr_color != 0 )
		attroff( COLOR_PAIR( curr_color ));
	attron( COLOR_PAIR( color ));
	return color;
}

void drawTerm( DnDMonster const *monster, const char* curr_comand ){

//HP {
	uint8_t text_size = snprintf( NULL, 0, " %i/%i", monster->hp, monster->max_hp );
	char text[text_size];
	snprintf( text, text_size, "%i/%i", monster->hp, monster->max_hp );

	move( LINES - 2, 0 );

	uint8_t curr_color = 0;
	for( uint8_t i = 0; i < COLS + 1; i++ ){
		curr_color = set_color( i, curr_color, MAX( monster->hp, 0 ), monster->max_hp );
		printw( "%c", determine_char( i, text, text_size ));
	}
	attroff( COLOR_PAIR( curr_color ));
//} HP

//CurrComand {
	mvprintw( LINES - 1, 0, ">%s", curr_comand );
//} CurrComand
}
