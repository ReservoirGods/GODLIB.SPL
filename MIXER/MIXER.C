/*************************************************************************************
 * GodLib Example Progam Suite
 * 
 * Demonstrates audio mixer
 *
 * PINK 13.10.18
 *************************************************************************************
*/

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\AUDIO\AUDIO.H>
#include	<GODLIB\AUDIO\AMIXER.H>
#include	<GODLIB\BIOS\BIOS.H>
#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\FILE\FILE.H>
#include	<GODLIB\FONT8X8\FONT8X8.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\PLATFORM\PLATFORM.H>
#include	<GODLIB\SCREEN\SCREEN.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>
#include	<GODLIB\VBL\VBL.H>
#include	<GODLIB\VIDEO\VIDEO.H>

#include	<stdio.h>

/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Hardware_Init( void );
void	Hardware_DeInit( void );

void	Test_Loop( void );

extern	void AudioMixer_TablesBuild();
extern void AudioMixer_Vbl();

sAmixerConfig	gExampleMixerConfig;

U16				gMyPalette[ 16 ] =
{
	0x000,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
	0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF
};

void	MixerBuffer_Render( U16 * apScreen, U16 aX, U16 aY, U16 aWidth, U16 aHeight );

/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : main( void )
* ACTION   : it begins  ...
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

S16	GodLib_Game_Main( S16 aArgCount, char * apArgs[] )
{
	(void)aArgCount;
	(void)apArgs;

#ifndef dGODLIB_PLATFORM_ATARI
	AudioMixer_TablesBuild();
#endif

	GemDos_Super( 0 );

	Platform_Init();

	Test_Loop();

	Platform_DeInit();

	return( 0 );
}



/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_Loop( void )
* ACTION   : Test_Loop
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Menu_Print( void )
{
	/* encode screen clear and cursor off into string using VT-52 codes */
	char *	lpString = "\033E\033f-GodLib Mixer Example-\n\r\n\r";
	char *	lpT1 = " [F1] - Left\n\r";
	char *	lpT2 = " [F2] - Right\n\r";
	char *	lpT3 = " [F3] - Centre\n\r";


	/* print information */
	GemDos_Cconws( lpString );
	GemDos_Cconws( lpT1 );
	GemDos_Cconws( lpT2 );
	GemDos_Cconws( lpT3 );

	GemDos_Cconws( " [F4] Pan Mode : " );
	switch( gExampleMixerConfig.mPanType )
	{
	case eMixer_PanType_Linear:
		GemDos_Cconws( "Linear" );
		break;
	case eMixer_PanType_ConstantPower:
		GemDos_Cconws( "ConstantPower" );
		break;
	case eMixer_PanType_PanLaw:
		GemDos_Cconws( "PanLaw" );
	default:
		break;
	}

	GemDos_Cconws( "\n\r [F5] Stereo Mode : " );
	if( gExampleMixerConfig.mStereoFlag )
		GemDos_Cconws( "Stereo" );
	else
		GemDos_Cconws( "Mono" );

	GemDos_Cconws( "\n\r\n\r [Space] - Quit\n\r" );

}

void	TestKey()
{
	for( ;; )
	{
		if( Bios_Bconstat( dBIOS_DEV_CONSOLE ) )
		{
			U32 lKey = Bios_Bconin( dBIOS_DEV_CONSOLE );
			char lString[ 64 ];
			sprintf( lString, "%08lX\n\r", lKey );
			GemDos_Cconws( lString );
		}
	}
}

/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_Loop( void )
* ACTION   : Test_Loop
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Test_Loop( void )
{
	char * lpSampleFileName = "voice.raw";
	sAudioDmaSound	lSound;

	gExampleMixerConfig = *AudioMixer_GetpConfig();

	Screen_Init( 320, 200, eGRAPHIC_COLOURMODE_4PLANE, eSCREEN_SCROLL_NONE );
	Video_SetPalST( &gMyPalette[ 0 ] );


/*	TestKey();*/

	lSound.mBits = eAUDIO_BITS_8;
	lSound.mFreq = eAUDIO_FREQ_12;
	lSound.mLoopingFlag = 0;
	lSound.mStereoFlag = 0;
	lSound.mLength = File_GetSize(lpSampleFileName);
	lSound.mpSound = File_Load(lpSampleFileName);

	Audio_MaximiseVolumeSigned( &lSound );
/*	Audio_ToggleSign( &lSound );*/

	gExampleMixerConfig.mFrequency = eAUDIO_FREQ_25;
	AudioMixer_SetConfig( &gExampleMixerConfig );

	AudioMixer_PlaySample( &lSound, eAMIXER_PAN_LEFT );

	for( ;; )
	{
		Screen_Update();
		Screen_Logic_ClearScreen();
		MixerBuffer_Render( Screen_GetpLogic(), 0, 100, 256, 80 );

		Font8x8_Print( "HELLO WORLD", Screen_GetpLogic(), 0, 0 );

		IKBD_Update();
		if( IKBD_GetKbdBytesWaiting() )
		{
			U8 lKey = IKBD_PopKbdByte();

			if( eIKBDSCAN_F1 == lKey )
			{
				AudioMixer_PlaySample( &lSound, eAMIXER_PAN_LEFT );
			}
			else if( eIKBDSCAN_F2 == lKey )
			{
				AudioMixer_PlaySample( &lSound, eAMIXER_PAN_RIGHT );
			}
			else if( eIKBDSCAN_F3 == lKey )
			{
				AudioMixer_PlaySample( &lSound, eAMIXER_PAN_CENTRE );
			}
			else if( eIKBDSCAN_F4 == lKey )
			{
				gExampleMixerConfig.mPanType++;
				if( gExampleMixerConfig.mPanType >= eMixer_PanType_Limit )
					gExampleMixerConfig.mPanType = 0;
				AudioMixer_SetConfig( &gExampleMixerConfig );
			}
			else if( eIKBDSCAN_F5 == lKey )
			{
				gExampleMixerConfig.mStereoFlag ^= 1;
				AudioMixer_SetConfig( &gExampleMixerConfig );
			}
			else if( eIKBDSCAN_SPACE == lKey )
			{
				break;
			}
		}
	}


	/* unload sound samples */
	File_UnLoad(lSound.mpSound);
}

void	MixerBuffer_Render( U16 * apScreen, U16 aX, U16 aY, U16 aWidth, U16 aHeight )
{
	U8 * lpBuffer = AudioMixer_GetpBuffer();
	U32 lBufferSize = AudioMixer_GetBufferSize();
	U32 lChunkSize = (lBufferSize / aWidth) / 2;
	U16 lMaxH = ( aHeight >> 1 );
	U16	y0 = (aY)+( lMaxH ) - ( lMaxH >> 1 );
	U16	y1 = (aY)+( lMaxH ) + ( lMaxH >> 1 );
	U16 x;

	(void)apScreen;

	for( x = 0; x < aWidth; x++ )
	{
		U16 lChunkTotal0=0;
		U16 lChunkTotal1 = 0;
		sGraphicRect	lRect;
/*#ifdef dGODLIB_PLATFORM_ATARI*/
#if 1
		lChunkTotal0 = lpBuffer[ 0 ] >> 2;
		lChunkTotal1 = lpBuffer[ 1 ] >> 2;
		lpBuffer += lChunkSize;
		lpBuffer += lChunkSize;
#else
		{
			U16 i;
			for( i = 0; i < lChunkSize;i++ )
			{
				lChunkTotal0 += *lpBuffer++;
				lChunkTotal1 += *lpBuffer++;
			}
		}
		lChunkTotal0 /= (U16)lChunkSize;
		lChunkTotal1 /= (U16)lChunkSize;

		lChunkTotal0 *= lMaxH;
		lChunkTotal1 *= lMaxH;

		lChunkTotal0 >>= 9;
		lChunkTotal1 >>= 9;
#endif

		lRect.mX = aX + x;
		lRect.mWidth = 1;
		lRect.mY = y0 - lChunkTotal0;
		lRect.mHeight = lChunkTotal0 << 1;

		Screen_Logic_DrawBox( &lRect, 1 );

		lRect.mY = y1 - lChunkTotal1;
		lRect.mHeight = lChunkTotal1 << 1;

		Screen_Logic_DrawBox( &lRect, 1 );
	}
}


/* ################################################################################ */
