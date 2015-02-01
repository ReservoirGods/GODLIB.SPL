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
#  DEFINES
################################################################################### */

#define	dBOX_X			10
#define	dBOX_Y			80
#define	dBOX_WIDTH		200
#define	dBOX_HEIGHT		60
#define	dBOX_COLOUR		1


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Test_Loop( void );
void	Box_Render( void );


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
* FUNCTION : main( void )
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


	while( !IKBD_GetKeyStatus(eIKBDSCAN_SPACE) )
	{
		Screen_Update();
		IKBD_Update();
		Box_Render();
	}

	Screen_DeInit(); 
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Box_Render( void )
* ACTION   : Box_Render
* CREATION : 02.01.2003 PNK
*-----------------------------------------------------------------------------------*/

void	Box_Render( void )
{
	sGraphicRect	lRect;
	
	lRect.mX      = dBOX_X;
	lRect.mY      = dBOX_Y;
	lRect.mWidth  = dBOX_WIDTH;
	lRect.mHeight = dBOX_HEIGHT;

	Screen_GetpLogicGraphic()->mpClipFuncs->DrawBox( 
		Screen_GetpLogicGraphic(), 
		&lRect, 
		dBOX_COLOUR );

}




/* ################################################################################ */
