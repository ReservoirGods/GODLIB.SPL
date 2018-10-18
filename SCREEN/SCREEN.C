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
#  PROTOTYPES
################################################################################### */

void	Hardware_Init( void );
void	Hardware_DeInit( void );

void	Test_Loop( void );

void	Screen_DrawBars( U16 * apScreen );

/* ###################################################################################
#	DATA
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
	U32		lBase;
	void *	lpScreenMem;
	U16 *	lpPhysic;

	/* set to a 320x200 16 colour screen*/
	Video_SetResolution( 320, 200, eGRAPHIC_COLOURMODE_4PLANE, 320 );

	/* allocate screen compatible memory*/
	lpScreenMem = mMEMSCREENCALLOC( 32000L + 255L );

	if( lpScreenMem )
	{
		/* all screen buffers have to be aligned to nearest 256 bytes*/
		lBase       = (U32)lpScreenMem;
		lBase       += 255L;
		lBase      &= 0xFFFFFF00L;

		lpPhysic    = (U16*)lBase;

		Video_SetPalST( &gMyPalette[ 0 ] );
		Screen_DrawBars( lpPhysic );
		Video_SetPhysic( lpPhysic );

		/* wait for space to be pressed */
		while( !IKBD_GetKeyStatus(eIKBDSCAN_SPACE) )
		{
			IKBD_Update();
		}

		mMEMSCREENFREE( lpScreenMem );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Screen_DrawBars( U16 * apScreen )
* ACTION   : Screen_DrawBars
* CREATION : 02.01.2003 PNK
*-----------------------------------------------------------------------------------*/

void	Screen_DrawBars( U16 * apScreen )
{
	U16		i;

	for( i=0; i<16000; i++ )
	{
		if( i & 8 )
			apScreen[ i ] = 0xFFFF;
		else
			apScreen[ i ] = 0;
	}
}



/* ################################################################################ */
