/*	Remove all comments from a c source file */
/*  This program attempts to remove all comments from a C/C+ source file, line-by-line */
/*  while placing the generated comment-less text into a new file */

/* john wroblewski wroblewski2 [at] wisc [dot] edu */
/* exercise from the c programming language by K&R ch 1 */

/* Interface: accepts filename as argument, produces new file titled 'source_no_comments.c' in same dir */
#include <stdio.h>
#define MAXLINE 1000
enum escapes_and_modes { FWDSLH = '/' , BKSLH = '\\' , SQUOTE = '\'' , DQUOTE = '"' , ASTERISK = '*' ,
                         NEWLINE = '\n' , INLINE_COMMENT = 0 , BLOCK_COMMENT = 1 , PROGRAM = 2 , STRING = 3 , CHARACTER = 4 };
int go_get_line( int * line , int maxline , FILE * read );
int main( int argc, char *argv[] ){
	if( argc != 2 )
		printf( "usage: %s [filename]\n" , argv[0] );
	else{
		FILE * file_read = fopen( argv[1] , "r" );
		if( file_read == NULL )
			printf( "failed to open %s\n" , argv[0] );
		else{
			FILE * file_write = fopen( "source_no_comments.c" , "w" );	/* open new file for writing */
			int len; 			   				/* holds the length of current string */
			int line[ MAXLINE ];						/* array that holds line being analyzed */
			int state = PROGRAM;						/* holds current state of position in source.. ie inside a comment or inside a string */

			while( ( len = go_get_line( line , MAXLINE , file_read ) ) > 0 ){
				int i , last_star;

				for( i = 0; i < len; ++i ){
					if( state == PROGRAM ){
						if( line[ i ] == FWDSLH ){
							if( line[ i + 1 ] == FWDSLH ){
								state = INLINE_COMMENT;
							}
							else if( line[ i + 1 ] == ASTERISK ){
								state = BLOCK_COMMENT;
								last_star = i + 1;
							}
							else
								fputc( line[ i ] , file_write );
						}else
						if( line[ i ] == DQUOTE ){
							state = STRING;
							fputc( DQUOTE , file_write );
						}else
						if( line[ i ] == SQUOTE ){
							state = CHARACTER;
							fputc( SQUOTE , file_write );
						}else
							fputc( line[ i ] , file_write );
					}else
					if( state == INLINE_COMMENT ){
						if( line[ i ] == NEWLINE ){
							state = PROGRAM;
							fputc( NEWLINE , file_write );
						}
					}else
					if( state == BLOCK_COMMENT ){
						if( line[ i ] == FWDSLH && ( i - 1 != last_star ) && line[ i - 1 ] == ASTERISK ) 	// i - 1 != last_star ensures that entry asterisk isnt the exit one
							state = PROGRAM;
					}else
					if( state == STRING ){
						if( line[ i ] == DQUOTE && line[ i - 1 ] != BKSLH )
							state = PROGRAM;
						fputc( line[ i ] , file_write );
					}
					else{  // if you've reached here, you're in CHARACTER territory and it's your last hope
						if( line[ i ] == SQUOTE && line[ i - 1 ] != BKSLH )
							state = PROGRAM;
						fputc( line[ i ] , file_write );
					}
				}
			}

			fclose( file_read );		//closing files
			fclose( file_write );
		}
	}
	return 0;
}
int go_get_line( int * s , int limit , FILE * file_read ){
	int c , i;
	for( i = 0; i < limit - 1 && ( c = fgetc( file_read ) ) != NEWLINE && c != EOF; ++i )
		s[ i ] = c;
	if( c == NEWLINE )
		s[ i++ ] = NEWLINE;
	s[ i ] = '\0';
	return i;
}
