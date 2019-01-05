/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB/DEBUGLOG/DEBUGLOG.H>
#include	<GODLIB/FILE/FILE.H>
#include	<GODLIB/GEMDOS/GEMDOS.H>
#include	<GODLIB/IKBD/IKBD.H>
#include	<GODLIB/INPUT/INPUT.H>
#include	<GODLIB/MEMORY/MEMORY.H>
#include	<GODLIB/PICTYPES/GOD.H>
#include	<GODLIB/PLATFORM/PLATFORM.H>
#include	<GODLIB/SCREEN/SCREEN.H>
#include	<GODLIB/SYSTEM/SYSTEM.H>
#include	<GODLIB/VIDEO/VIDEO.H>


/* ###################################################################################
#  DATA
################################################################################### */

sGod * gpGodPaintFile = 0;

void	GodPaint_Show( sGraphicCanvas * apCanvas,sGod * apGod );
void	Test_Loop( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : main( void )
* ACTION   : it begins  ...
* CREATION : 05.01.2019 PNK
*-----------------------------------------------------------------------------------*/

S16	GodLib_Game_Main( S16 aArgCount, char * apArgs[] )
{
	(void)aArgCount;
	(void)apArgs;
	
	GemDos_Super( 0 );

	Platform_Init();

	Test_Loop();

	Platform_DeInit();

	return( 0 );
}

/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_Loop( void )
* ACTION   : Test_Loop
* CREATION : 05.01.2019 PNK
*-----------------------------------------------------------------------------------*/

void	Test_Loop( void )
{
	sGod *			godPaintFile;
	U8				redrawFlag = 2;

	/* turn the blitter on */
	/* NOTE: blitter must be enabled in GEM (OPTIONS->BLITTER on desktop) */
	Graphic_SetBlitterEnable( 1 );

	godPaintFile = (sGod*)File_Load( "IMAGE.GOD" );

	if( !godPaintFile )
	{
		printf( "couldn't find god paint file" );
		GemDos_Cnecin();
		return;
	}

	/* allow code to run on little endian (non atari) platforms */
	Endian_FromBigU16( &godPaintFile->mHeader.mHeight );
	Endian_FromBigU16( &godPaintFile->mHeader.mWidth  );


	Screen_Init( 320, 240, eGRAPHIC_COLOURMODE_16BPP, eSCREEN_SCROLL_NONE );

	while( 0 == (eINPUTKEYSTATUS_HIT & IKBD_GetKeyStatus(eIKBDSCAN_SPACE )) )
	{
		Screen_Update();
		IKBD_Update();
		if( redrawFlag )
		{
			GodPaint_Show( Screen_GetpLogicGraphic(), godPaintFile );
			redrawFlag--;
		}
	}

	File_UnLoad( godPaintFile );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : GodPaint_Show( sGraphicCanvas * apCanvas,sGod * apGod,U16 aX,U16 aY )
* ACTION   : renders a godpaint image to screen
* CREATION : 05.01.2019 PNK
*-----------------------------------------------------------------------------------*/

void	GodPaint_Show( sGraphicCanvas * apCanvas, sGod * apGod )
{
	U16 *	lpSrc0;
	U16 *	lpDst0;
	U16		x,y;
	
	if( apCanvas && apGod )
	{
		lpDst0 = apCanvas->mpVRAM;
		lpSrc0 = apGod->mPixels;
		for( y = apGod->mHeader.mHeight; y; y-- )
		{
			U16 * lpDst1 = lpDst0;
			U16 * lpSrc1 = lpSrc0;

			for( x=apGod->mHeader.mWidth; x; x-- )
				*lpDst1++ = *lpSrc1++;

			lpSrc0 += apGod->mHeader.mWidth;
			lpDst0 += apCanvas->mWidth;
		}
	}
}


/* ################################################################################ */