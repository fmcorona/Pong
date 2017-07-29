#include "includes/pong/globals.h"
#include "includes/pong/menu/confmenu.h"

void fnPrintKeyboard( int x, int y )
{
	int iInitX = x, iInitY = y;
	char cCharacter;
	FILE* pFile;

	pFile = fnOpenFileToRead( "resource/keyboard.txt" );

	cCharacter = fgetc( pFile );

	gotoxy( x, y );

	while( cCharacter != EOF )
	{
		if( cCharacter == '-' )
			printf( "%c", 196 );
		else if( cCharacter == '|' )
			printf( "%c", 179 );
		else if ( cCharacter == '\n' )
			gotoxy( x, ++y );
		else
			printf( "%c", cCharacter );

		cCharacter = fgetc( pFile );
	}

	fnCloseFile( pFile );
	// up
	gotoxy( iInitX + 50, iInitY + 1 );
	printf( "%c", 30 );
	// down
	gotoxy( iInitX + 50, iInitY + 5 );
	printf( "%c", 31 );
	// left
	gotoxy( iInitX + 46, iInitY + 3 );
	printf( "%c", 17 );
	// right
	gotoxy( iInitX + 54, iInitY + 3 );
	printf( "%c", 16 );
}

void fnConfiguration(  )
{
	char cCharacter;
	FILE* pFile;

	clrscr(  );

	pFile = fnOpenFileToRead( "resource/config.txt" );

	cCharacter = fgetc( pFile );

	while( cCharacter != EOF )
	{
		printf( "%c", cCharacter );		

		cCharacter = fgetc( pFile );
	}

	fnCloseFile( pFile );

	gotoxy( 17, 4 );
	printf( "%d mins", g_iLimitTime );

	fnPrintControls( PLAYER_1, 10, 9 );
	fnPrintControls( PLAYER_2, 10, 13 );

	fnPrintKeyboard( 13, 16 );

	getch(  );
}