/*************************************************************************************
 * GodLib Example Progam Suite
 * 
 * Demonstrates basic screen functionality
 *
 * PINK 01.01.03
 *************************************************************************************
*/

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\CLI\CLI.H>
#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\GRAPHIC\GRAPHIC.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\MEMORY\MEMORY.H>
#include	<GODLIB\PLATFORM\PLATFORM.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\VBL\VBL.H>
#include	<GODLIB\VIDEO\VIDEO.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Test_Loop( void );

void	Test_HelpCli( const char * apArgs );
void	Test_NumberCli( const char * apArgs );
void	Test_TosCli( const char * apArgs );


/* ###################################################################################
#  DATA
################################################################################### */

U16				gMyPalette[ 16 ] =
{
	0x000,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
	0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF
};



/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : GodLib_Game_Main( S16 aArgCount, char * apArgs[] ) )
* ACTION   : it begins  ...
* CREATION : 02.01.2015 PNK
*-----------------------------------------------------------------------------------*/

S16	GodLib_Game_Main( S16 aArgCount, char * apArgs[] )
{
	GemDos_Super( 0 );

	Platform_Init();

	Test_Loop();

	Platform_DeInit();

	return( 0 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_Loop( void )
* ACTION   : Test_Loop
* CREATION : 18.12.2002 PNK
*-----------------------------------------------------------------------------------*/

void	Test_Loop( void )
{
	Screen_Init( 320, 200, eGRAPHIC_COLOURMODE_4PLANE, eSCREEN_SCROLL_NONE );
	Video_SetPalST( &gMyPalette[ 0 ] );

	Cli_Init();

	Cli_CmdInit( "help",   Test_HelpCli   );
	Cli_CmdInit( "number", Test_NumberCli );
	Cli_CmdInit( "tos",    Test_TosCli    );

	Cli_PrintLine( "GodLib CLI" );
	Cli_PrintLine( "" );
	Cli_PrintLine( "cmds: help, number, tos" );

	Cli_Main();


	Cli_DeInit();

	Screen_DeInit(); 
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_HelpCli( const char * apArgs )
* ACTION   : Test_HelpCli
* CREATION : 03.01.2003 PNK
*-----------------------------------------------------------------------------------*/

void	Test_HelpCli( const char * apArgs )
{
	Cli_PrintLine( "you asked for help!" );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_NumberCli( const char * apArgs )
* ACTION   : Test_NumberCli
* CREATION : 03.01.2003 PNK
*-----------------------------------------------------------------------------------*/

void	Test_NumberCli( const char * apArgs )
{
	S32		lNum;
	char	lString[ 128 ];

	lNum = Cli_GrabNumber( apArgs );

	sprintf( lString, "your number is : %ld", lNum );

	Cli_PrintLine( lString );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_TosCli( const char * apArgs )
* ACTION   : Test_TosCli
* CREATION : 03.01.2003 PNK
*-----------------------------------------------------------------------------------*/

void	Test_TosCli( const char * apArgs )
{
	char	lString[ 128 ];
	
	sprintf( lString, "TOS Verion : %x", System_GetTosVersion() );

	Cli_PrintLine( lString );
}


/* ################################################################################ */
