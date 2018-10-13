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
#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\FILE\FILE.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>
#include	<GODLIB\VBL\VBL.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Hardware_Init( void );
void	Hardware_DeInit( void );

void	Test_Loop( void );

extern	void AudioMixer_TablesBuild();

sAmixerConfig	gExampleMixerConfig;

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

	Hardware_Init();

	Test_Loop();

	Hardware_DeInit();

	return( 0 );
}



/*-----------------------------------------------------------------------------------*
* FUNCTION : Hardware_Init( void )
* ACTION   : Hardware_Init
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Hardware_Init( void )
{
	System_Init();
	Vbl_Init();
	IKBD_Init();
	Audio_Init();
	AudioMixer_Init();
	AudioMixer_Enable();
	gExampleMixerConfig = *AudioMixer_GetpConfig();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Hardware_DeInit( void )
* ACTION   : Hardware_DeInit
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Hardware_DeInit( void )
{
	AudioMixer_DeInit();
	Audio_DeInit();
	IKBD_DeInit();
	Vbl_DeInit();
	System_DeInit();
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

	GemDos_Cconws( "\n\r\n\r [Space] - Quit\n\r" );

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

	lSound.mBits = eAUDIO_BITS_8;
	lSound.mLoopingFlag = 0;
	lSound.mStereoFlag = 0;
	lSound.mLength = File_GetSize(lpSampleFileName);
	lSound.mpSound = File_Load(lpSampleFileName);

	Audio_MaximiseVolumeSigned( &lSound );

	/* loop until space pressed */
	for(;;)
	{
		U8 lKey;
		/* wait for key */
		Menu_Print();
		while( !IKBD_GetKbdBytesWaiting());
		lKey = IKBD_PopKbdByte();

		if( eIKBDSCAN_F1 == lKey )
		{
			AudioMixer_PlaySample( &lSound, eAMIXER_PAN_LEFT );
		}
		else if( eIKBDSCAN_F2 == lKey )
		{
			AudioMixer_PlaySample( &lSound, eAMIXER_PAN_RIGHT );
		}
		else if (eIKBDSCAN_F3 == lKey)
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
		else if( eIKBDSCAN_SPACE == lKey )
		{
			break;
		}
	}

	/* unload sound samples */
	File_UnLoad(lSound.mpSound);
}


/* ################################################################################ */
