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
#include	<GODLIB\SYSTEM\SYSTEM.H>
#include	<GODLIB\VBL\VBL.H>
#include	<GODLIB\VIDEO\VIDEO.H>


/* ###################################################################################
#  DEFINES
################################################################################### */


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Hardware_Init( void );
void	Hardware_DeInit( void );

void	Test_Loop( void );

void	Test_ScreenInit( void );
void	Test_ScreenDeInit( void );
void	Test_ScreenSwap( void );


/* ###################################################################################
#  DATA
################################################################################### */

void *			gpScreenMem;
U16 *			gpPhysic;
U16 *			gpLogic;


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
	(void)aArgCount;
	(void)apArgs;
	
	GemDos_Super( 0 );

	Hardware_Init();

	Test_Loop();

	Hardware_DeInit();

	return( 0 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Hardware_Init( void )
* ACTION   : Hardware_Init
* CREATION : 18.12.2002 PNK
*-----------------------------------------------------------------------------------*/

void	Hardware_Init( void )
{
	System_Init();
	Vbl_Init();
	Video_Init();
	IKBD_Init();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Hardware_DeInit( void )
* ACTION   : Hardware_DeInit
* CREATION : 18.12.2002 PNK
*-----------------------------------------------------------------------------------*/

void	Hardware_DeInit( void )
{
	Video_DeInit();
	IKBD_DeInit();
	Vbl_DeInit();
	System_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_Loop( void )
* ACTION   : Test_Loop
* CREATION : 18.12.2002 PNK
*-----------------------------------------------------------------------------------*/

void	Test_Loop( void )
{
	U32		lAligned;

	gpScreenMem = mMEMSCREENCALLOC( 64000L + 255L );

	lAligned    = (U32)gpScreenMem;
	lAligned   += 255L;
	lAligned   &= 0xFFFFFF00L;

	gpPhysic    = (U16*)lAligned;

	lAligned   += 32000L;

	gpLogic     = (U16*)lAligned;

	Video_SetMode( 320, 200, eVIDEO_MODE_4PLANE, 320, 0, 1 );

	while( !IKBD_GetKeyStatus(eIKBDSCAN_SPACE) )
	{
		Test_ScreenSwap();
		IKBD_Update();
	}

	mMEMSCREENFREE( gpScreenMem );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Screen_Swap( void )
* ACTION   : Screen_Swap
* CREATION : 02.01.2003 PNK
*-----------------------------------------------------------------------------------*/

void	Test_ScreenSwap( void )
{
	U16	*	lpTemp;
	
	lpTemp   = gpPhysic;
	gpPhysic = gpLogic;
	gpLogic  = lpTemp;

	Video_SetPhysic( gpPhysic );
	Vbl_WaitVbl();
}


/* ################################################################################ */
