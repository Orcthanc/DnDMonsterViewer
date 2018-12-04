#include "Term.h"

#include <stdio.h>
#include <unistd.h>

void getTermSize( TermSize* t_size ){
	#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );

	t_size->x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	t_size->y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	#else
	struct winsize w;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );

	t_size->x = w.ws_row;
	t_size->y = w.ws_col;
	#endif
}

void drawTerm( DnDMonster const *monster ){
	TermSize t_size;
	getTermSize( &t_size );

	printf( "\033[2J" );

	//HP
	printf( "\033[%i;0H", t_size.y - 1 );
	uint8_t text_size = snprintf( NULL, 0, " %i/%i", monster->hp, monster->max_hp );
	
	uint8_t red_chars = monster->hp * t_size.x / monster->max_hp;
	printf( "%i %i ", red_chars, t_size.x );
}
