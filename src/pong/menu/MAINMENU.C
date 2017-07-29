#include "includes/pong/globals.h"
#include "includes/pong/menu/mainmenu.h"
#include "includes/pong/menu/playmenu.h"
#include "includes/pong/menu/exitmenu.h"
#include "includes/pong/menu/infomenu.h"


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

	pFile = fnOpenFileToRead( "resource/pong.txt" );

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

void fnBuildMenu( int iTypeLogo )
{
	clrscr(  );

	fnBuildLogo( 17, 2, iTypeLogo );
	fnBuildOptions(  );
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

void fnStartMenu( )
{
	int iOption;
	do
	{
		fnBuildMenu( 3 );

		iOption = fnChooseOption( );
		fnCarryOutOption( iOption );

	} while ( iOption != EXIT );
}