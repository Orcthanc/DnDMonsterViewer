#include "Monster.h"
#include "Parser.h"

#include <stdio.h>
#include <string.h>
#include <ncurses.h>

static void readFile( char* buffer, FILE* file ){
	char* cur_char = buffer;
	while( (*cur_char++ = fgetc( file )) != EOF );
	*--cur_char = '\0';
}

static int countChars( const char* buffer, const char* chars ){
	int num = 0;
	const char* i1 = buffer;
	const char* i2;
	while( *i1 ){
		i2 = chars;
		while( *i2 ){
			if( *i1 == *i2 ){
				num++;
				break;
			}
			i2++;
		}
		i1++;
	}
	return num;
}

static char* strcopy( const char* string ){
	char* newString = malloc( strlen( string ) + 1 );
	strcpy( newString, string );
	return newString;
}

static uint16_t tokenize( FILE* file, char*** return_value ){
	fseek( file, 0L, SEEK_END );
	char buffer[ ftell( file ) + 1 ];
	fseek( file, 0L, SEEK_SET );
	readFile( buffer, file );

	uint16_t tokens = countChars( buffer, "{}:," ) * 2 - 2;

	*return_value = (char**)malloc( tokens * sizeof( char* ));

	char buffertemp[4096] = "\0";

	char* temp = buffertemp;
	int index = 0;
	int inWord = 0;
	for( char* curr_char = buffer; *curr_char; curr_char++){
		switch( *curr_char ){
			case '{':
			case '}':
			case ',':
			case ':':
				if( inWord ){
					*temp = *curr_char;
					temp++;
				}else{
					(*return_value)[index] = malloc(2);
					*((*return_value)[index++]) = *curr_char;
				}
				break;
			case '"':
				if( inWord ){
					*temp = '\0';
					(*return_value)[index++] = strcopy( buffertemp );
					temp = buffertemp;
					inWord = 0;
				}else{
					inWord = 1;
				}
				break;
			case '\t':
			case '\r':
			case '\n':
				if( inWord ){
					*temp = *curr_char;
					temp++;
				}
				break;
			case ' ':
				if( inWord ){
					*temp = ' ';
					temp++;
				}
				break;
			default:
				if( inWord ){
					*temp = *curr_char;
					temp++;
				}
				else{
					fprintf( stderr, "Possible error during tokenization of the JSON. Are all names/strings encapsulated in \"? %s %u\n", curr_char, (uint32_t)*curr_char );
				}
		}
	}

	return index;
}

static JSONObjectArray* parse( char** content ){
	
}

void createDnDMonsterJSON( DnDMonster* monster, const char* path ){
	FILE* json = fopen( path, "r" );
	
	if( !monster )
		monster = (DnDMonster*)malloc( sizeof( DnDMonster ));
	
	char** tokens = NULL;

	int token_length = tokenize( json, &tokens );

	for( uint16_t i = 0; i < token_length; ++i )
		fprintf( stderr, "%s\n\r", tokens[i] );

	JSONObjectArray* json_struct = parse( tokens );

	fclose( json );
}
