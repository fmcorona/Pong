
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

extern int g_iLimitTime;

extern char g_cUpPlayer1;
extern char g_cDownPlayer1;

extern char g_cUpPlayer2;
extern char g_cDownPlayer2;

void fnPrintControls( int iPlayer, int x, int y );
FILE* fnOpenFileToRead( char* strNameOfFile );
void fnCloseFile( FILE* pFile );