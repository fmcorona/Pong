#include "includes/pong/globals.h"

int g_iLimitTime = 5;

char g_cUpPlayer1 = 'w';
char g_cDownPlayer1 = 's';

char g_cUpPlayer2 = 30;
char g_cDownPlayer2 = 31;


FILE* fnOpenFileToRead( char* strNameOfFile )
{
	FILE* pFile;

	pFile = fopen( strNameOfFile, "r" );

	if ( pFile == NULL )
	{
		printf( " Error: Could not open the file '%s'\n", strNameOfFile );

		printf( "\n\n Press any key to exit..." );
		getch( );

		exit( 1 );
	}

	return pFile;
}

void fnCloseFile( FILE* pFile ) { fclose( pFile ); }

void fnPrintControls( int iPlayer, int x, int y )
{
	char cUp, cDown;

	if ( iPlayer == PLAYER_1 )
	{
		cUp = g_cUpPlayer1;
		cDown = g_cDownPlayer1;

	}
	else
	{
		cUp = g_cUpPlayer2;
		cDown = g_cDownPlayer2;
	}
	// up
	gotoxy( x, y );
	printf( "[%c]\n", cUp );
	// down
	gotoxy( x, y + 1 );
	printf( "[%c]\n", cDown );
}