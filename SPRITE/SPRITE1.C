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
#include	<GODLIB\FILE\FILE.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\MEMORY\MEMORY.H>
#include	<GODLIB\PLATFORM\PLATFORM.H>
#include	<GODLIB\PICTYPES\DEGAS.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SPRITE\SPRITE.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>
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
	U16				lScreenIndex = 0;
	sSprite *		lpSprite;

	Screen_Init( 320, 200, eGRAPHIC_COLOURMODE_4PLANE, eSCREEN_SCROLL_NONE );

	gpPicture = File_Load( "SPRITE.PI1" );

	if( gpPicture )
	{
		Video_SetPalST( &gpPicture->mHeader.mPalette[ 0 ] );

		lPos.mX = 0;
		lPos.mY = 0;

		lPosSaved[ 0 ] = lPos;
		lPosSaved[ 1 ] = lPos;

		lAddX  = 1;
		lAddY  = 1;

		lpSprite = Sprite_Create(
			&gpPicture->mPixels[ 0 ],	/* source graphics */
			&gpPicture->mPixels[ 0 ],	/* source mask */
			16,	/* width */
			16,	/* height */
			4,	/* planes */
			0,	/* mask planes */
			0	/* opaque flag */
			);

		while( !IKBD_GetKeyStatus(eIKBDSCAN_SPACE) )
		{
			lScreenIndex ^= 1;
			Screen_Update();
			IKBD_Update();


			/* clear old sprite */

			lRect.mX = lPosSaved[ lScreenIndex ].mX;
			lRect.mY = lPosSaved[ lScreenIndex ].mY;
			lRect.mWidth = 16;
			lRect.mHeight = 16;
			lPosSaved[ lScreenIndex ] = lPos;
			Screen_GetpLogicGraphic()->mpClipFuncs->DrawBox( Screen_GetpLogicGraphic(), &lRect, 0 );


			/* draw new sprite */

			Screen_GetpLogicGraphic()->mpClipFuncs->DrawSprite(
				Screen_GetpLogicGraphic(),
				&lPos,
				lpSprite );


			/* calculate new sprite pos */

			if( lAddX > 0 )
			{
				lPos.mX++;
				if( lPos.mX > (320-16) )
				{
					lPos.mX = 320-16;
					lAddX  = -1;
				}
			}
			else
			{
				lPos.mX--;
				if( lPos.mX < 0 )
				{
					lPos.mX = 0;
					lAddX  = 1;
				}
			}

			if( lAddY > 0 )
			{
				lPos.mY++;
				if( lPos.mY > (200-16) )
				{
					lPos.mY = 200-16;
					lAddY  = -1;
				}
			}
			else
			{
				lPos.mY--;
				if( lPos.mY < 0 )
				{
					lPos.mY = 0;
					lAddY  = 1;
				}
			}

		}
	}

	File_UnLoad( gpPicture );
}



/* ################################################################################ */
