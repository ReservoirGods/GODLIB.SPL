/*************************************************************************************
 * GodLib Example Progam Suite
 * 
 * Demonstrates basic blitter functionality
 *
 *  Note: Blitter has to be enable in GEM [OPTIONS->BLITTER] for this to work
 *  If no blitter is found, or it is disable in GEM, this resorts to CPU rendering
 * 
 * PINK 05.01.18
 *************************************************************************************
*/

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\FILE\FILE.H>
#include	<GODLIB\FONT8X8\FONT8X8.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\PLATFORM\PLATFORM.H>
#include	<GODLIB\PICTYPES\DEGAS.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\VBL\VBL.H>
#include	<GODLIB\VIDEO\VIDEO.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Test_Loop( void );


/* ###################################################################################
#  DATA
################################################################################### */

sDegas *		gpPicture;


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
* CREATION : 18.12.2002 PNK
*-----------------------------------------------------------------------------------*/

void	Test_Loop( void )
{
	sGraphicPos		lPosSaved[ 2 ];
	sGraphicPos		lPos;
	sGraphicRect	lRect;
	S16				lAddX,lAddY;
	sSprite *		lpSprite;
	U16 *			lpMsk;
	U8				exitFlag = 0;

	/* turn the blitter on */
	/* NOTE: blitter must be enabled in GEM (OPTIONS->BLITTER on desktop) */
	Graphic_SetBlitterEnable( 1 );

	gpPicture = File_Load( "SPRITE.PI1" );

	if( !gpPicture )
	{
		printf( "couldn't find sprite file" );
		GemDos_Cnecin();
		return;
	}

	Screen_Init( 320, 200, eGRAPHIC_COLOURMODE_4PLANE, eSCREEN_SCROLL_NONE );

	Video_SetPalST( &gpPicture->mHeader.mPalette[ 0 ] );

	lPos.mX = 0;
	lPos.mY = 0;

	lPosSaved[ 0 ] = lPos;
	lPosSaved[ 1 ] = lPos;

	/* generate a mask for the sprite	*/
	/* when using tools pipeline, this is generally done with the MASKMAKE tool, and the sprite is constructed with BSBMAKER */

	lpMsk = Sprite_MaskCreate(
		&gpPicture->mPixels[ 0 ],	/* source graphics */
		16,	/* width */
		16,	/* height */
		4,	/* planes */
		4,	/* mask planes */
		0	/* opaque flag */
		);

	lpSprite = Sprite_Create(
		&gpPicture->mPixels[ 0 ],	/* source graphics */
		lpMsk,	/* source mask */
		16,	/* width */
		16,	/* height */
		4,	/* planes */
		4,	/* mask planes */
		0	/* opaque flag */
		);

	Sprite_MaskDestroy( lpMsk );

	lAddX = 1;
	lAddY = 1;
	while( !exitFlag )
	{
		U16 onOffX = 15 * 8;

		while( IKBD_GetKbdBytesWaiting() )
		{
			U8 key = IKBD_PopKbdByte();
			if( eIKBDSCAN_SPACE == key )
			{
				exitFlag = 1;
			}
			else if( eIKBDSCAN_F1 == key )
			{
				/* toggle blitter on/off if F1 is pressed */
				Graphic_SetBlitterEnable( (Graphic_GetBlitterEnable()&1) ^ 1 );
			}
		}

		Screen_Update();
		IKBD_Update();

		Font8x8_Print( "F1: BLITTER [ O", Screen_GetpLogic(), 0, 0 );
		if( Graphic_GetBlitterEnable() )
		{
			Font8x8_Print( "N ] ", Screen_GetpLogic(), onOffX, 0 );
		}
		else
		{
			Font8x8_Print( "FF ]", Screen_GetpLogic(), onOffX, 0 );
		}

		/* clear old sprite */
		lRect.mX = lPosSaved[ Screen_GetLogicIndex() ].mX;
		lRect.mY = lPosSaved[ Screen_GetLogicIndex() ].mY;
		lRect.mWidth = 16;
		lRect.mHeight = 16;
		Screen_Logic_DrawBox_Clip( &lRect, 0 );

		/* save current sprite position*/
		lPosSaved[ Screen_GetLogicIndex() ] = lPos;

		/* draw new sprite to logical screen (backbuffer) */
		Screen_Logic_DrawSprite_Clip( &lPos, lpSprite );

		/* calculate new sprite pos */
		lPos.mX += lAddX;

		if( lPos.mX >= (320-16) )
			lAddX  = -1;
		else if( lPos.mX < 0 )
			lAddX  = 1;

		lPos.mY += lAddY;

		if( lPos.mY >= (200-16) )
			lAddY  = -1;
		else if( lPos.mY < 9 )
			lAddY  = 1;
	}

	File_UnLoad( gpPicture );
}


/* ################################################################################ */
