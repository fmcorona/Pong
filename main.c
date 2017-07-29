
#include <dos.h>
#include "main.h"
#include "includes/pong/menu/mainmenu.h"

int main(  )
{
	_setcursortype( _NOCURSOR );

	fnStartMenu( );
	
	_setcursortype( _NORMALCURSOR );

	return 0;
}
