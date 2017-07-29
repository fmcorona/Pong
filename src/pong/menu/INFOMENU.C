#include "includes/pong/globals.h"
#include "includes/pong/menu/infomenu.h"

void fnInformation(  )
{
	char cCharacter;
	FILE* pFile;

	clrscr(  );

	pFile = fnOpenFileToRead( "resource/info.txt" );

	cCharacter = fgetc( pFile );

	while( cCharacter != EOF )
	{
		printf( "%c", cCharacter );		

		cCharacter = fgetc( pFile );
	}

	fnCloseFile( pFile );

	fnPrintControls( PLAYER_1, 10, 11 );
	fnPrintControls( PLAYER_2, 10, 15 );

	getch(  );
}