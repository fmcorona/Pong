#include <stdio.h>
#include <conio.h>

#define ESC 27
#define ENTER 13
#define UP_ARROW 72
#define DOWN_ARROW 80

#define OPTIONS 4
#define OPTION_EXIT 3
#define EXIT 3

#define NO_BLINK 0
#define TEXT_COLOR LIGHTGRAY

#define PLAYER_1 1
#define PLAYER_2 2

int g_iLimitTime = 5;

char g_cUpPlayer1 = 'w';
char g_cDownPlayer1 = 's';

char g_cUpPlayer2 = 30;
char g_cDownPlayer2 = 31;

FILE* fnOpenFileToRead( char* strNameOfFile );
void fnCloseFile( FILE* pFile );

int fnTypeLogo( int iType );
void fnBuildLogo( int x, int y, int iType );
void fnBuildOptions(  );
void fnPrintOption( int iOption, int iColor, int iBlink );
void fnBuildMenu( int iTypeLogo );

int fnChooseOption(  );
void fnCarryOutOption( int iOption );

void fnPlay(  );
void fnConfiguration(  );
void fnInformation(  );
void fnExit(  );

void fnPrintKeyboard( int x, int y );
void fnPrintControls( int iPlayer, int x, int y );

int main(  )
{
	int iOption;

	_setcursortype( _NOCURSOR );

	do
	{
		fnBuildMenu( 3 );

		iOption = fnChooseOption( );
		fnCarryOutOption( iOption );

	} while ( iOption != EXIT );
	
	_setcursortype( _NORMALCURSOR );

	return 0;
}

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

int fnTypeLogo( int iType )
{
	if ( iType == 1)
		return 176;

	if ( iType == 2)
		return 177;
	
	if ( iType == 3)
		return 178;

	return 219;
}

void fnBuildLogo( int x, int y, int iType )
{
	int iAscii = fnTypeLogo( iType );	
	char cCharacter;
	FILE* pFile;

	pFile = fnOpenFileToRead( "pong.txt" );

	cCharacter = fgetc( pFile );

	gotoxy( x, y );

	while( cCharacter != EOF )
	{
		if( cCharacter == '#' )
			printf( "%c", iAscii );
		else if ( cCharacter == '\n' )
			gotoxy( x, ++y );
		else
			printf( "%c", cCharacter );		

		cCharacter = fgetc( pFile );
	}

	fnCloseFile( pFile );
}

void fnBuildOptions(  )
{
	gotoxy( 33, 16 );
	printf( "P    L    A    Y" );

	gotoxy( 29, 18 );
	printf( "O   P   T   I   O  N   S" );

	gotoxy( 25, 20 );
	printf( "I  N  F  O  R  M  A  T  I  O  N" );

	gotoxy( 34, 22 );
	printf( "Q   U   I   T" );
}

// TODO: MEJORAR QUiTAR EL SWITCH
void fnPrintOption( int iOption, int iColor, int iBlink )
{
	textcolor( iColor + iBlink );

	switch( iOption )
	{
		case 0:
			gotoxy( 33, 16 );
			cprintf( "P    L    A    Y" );
			break;

		case 1:
			gotoxy( 29, 18 );
			cprintf( "O   P   T   I   O  N   S" );
			break;

		case 2:
			gotoxy( 25, 20 );
			cprintf( "I  N  F  O  R  M  A  T  I  O  N" );
			break;

		case 3:
			gotoxy( 34, 22 );
			cprintf( "Q   U   I   T" );
			break;

		default: ;
	}

	textcolor( TEXT_COLOR );
}

void fnBuildMenu( int iTypeLogo )
{
	clrscr(  );

	fnBuildLogo( 17, 2, iTypeLogo );
	fnBuildOptions(  );
}

int fnChooseOption(  )
{
	int iOption = 0;
	char cKey;

	fnPrintOption( iOption, LIGHTGRAY, BLINK );

	do
	{
		if( kbhit( ) )
		{
			cKey = getch( );

			if ( cKey == 0 )
				cKey = getch( );

			if( cKey == UP_ARROW )
			{
				fnPrintOption( iOption, LIGHTGRAY, NO_BLINK );
				
				iOption--;

				if ( iOption < 0 )
					iOption = OPTIONS - 1;

				fnPrintOption( iOption, LIGHTGRAY, BLINK );
			}
			else if ( cKey == DOWN_ARROW )
			{
				fnPrintOption( iOption, LIGHTGRAY, NO_BLINK );

				iOption = ( iOption + 1 ) % OPTIONS;

				fnPrintOption( iOption, LIGHTGRAY, BLINK );
			}
			else if ( cKey == ESC )
			{
				// Para salir del juego si se da doble [Esc] o si
				// se está en la opción exit y se presiona [Esc].
				if ( iOption == OPTION_EXIT )
					break;

				fnPrintOption( iOption, LIGHTGRAY, NO_BLINK );

				iOption = OPTION_EXIT;

				fnPrintOption( iOption, LIGHTGRAY, BLINK );
			}
		}

	} while( cKey != ENTER );

	return iOption;
}

void fnCarryOutOption( int iOption )
{
	switch( iOption )
	{
		case 0: fnPlay(  );
			break;

		case 1: fnConfiguration(  );
			break;

		case 2: fnInformation(  );
			break;

		case 3: fnExit(  );
			break;

		default: ;
	}
}

void fnPlay(  )
{
	clrscr(  );

	printf( "\n  Play" );
	getch(  );
}

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

void fnConfiguration(  )
{
	char cCharacter;
	FILE* pFile;

	clrscr(  );

	pFile = fnOpenFileToRead( "config.txt" );

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

void fnInformation(  )
{
	char cCharacter;
	FILE* pFile;

	clrscr(  );

	pFile = fnOpenFileToRead( "info.txt" );

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

void fnExit(  )
{
	clrscr(  );

	printf( "\n  Exit" );
	getch(  );
}

void fnPrintKeyboard( int x, int y )
{
	int iInitX = x, iInitY = y;
	char cCharacter;
	FILE* pFile;

	pFile = fnOpenFileToRead( "keyboard.txt" );

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
