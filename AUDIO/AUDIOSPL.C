/*************************************************************************************
 * GodLib Example Progam Suite
 * 
 * Demonstrates audio sample playback
 *
 * PINK 09.05.18
 *************************************************************************************
*/

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\AUDIO\AUDIO.H>
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
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Hardware_DeInit( void )
* ACTION   : Hardware_DeInit
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Hardware_DeInit( void )
{
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
	char *	lpString = "\033E\033f-GodLib Audio Sample-\n\r\n\r";
	char *	lpT1 = " [F1] - Sample 1 (string loop)\n\r";
	char *	lpT2 = " [F2] - Sample 2 (female voice)\n\r";
	char *	lpT3 = " [F3] - Sample 3 (stereo sound)\n\r\n\r";
	char *	lpQ  = " [Space] - Quit\n\r";


	/* print information */
	GemDos_Cconws( lpString );
	GemDos_Cconws( lpT1 );
	GemDos_Cconws( lpT2 );
	GemDos_Cconws( lpT3 );
	GemDos_Cconws( lpQ );

}

/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_Loop( void )
* ACTION   : Test_Loop
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Test_Loop( void )
{

	char * lpSampleFileNames[ 3 ]=
	{
		"loop.raw",
		"voice.raw",
		"stereo.raw",
	};
	sAudioDmaSound	lSounds[3];

	U16 i;
	U8	lSampleIndex = 0;
	U8	lExitFlag = 0;

	for (i = 0; i < 3; i++)
	{
		lSounds[i].mBits = eAUDIO_BITS_8;
		lSounds[i].mStereoFlag = 0;
		lSounds[i].mLength = File_GetSize(lpSampleFileNames[i]);
		lSounds[i].mpSound = File_Load(lpSampleFileNames[i]);
		lSounds[i].mStereoFlag = 0;
	}

	lSounds[0].mLoopingFlag = 1;
	lSounds[0].mFreq = eAUDIO_FREQ_25;
	lSounds[0].mStereoFlag = 0;

	lSounds[1].mLoopingFlag = 0;
	lSounds[1].mFreq = eAUDIO_FREQ_12;
	lSounds[1].mStereoFlag = 0;

	lSounds[2].mLoopingFlag = 0;
	lSounds[2].mFreq = eAUDIO_FREQ_12;
	lSounds[2].mStereoFlag = 1;

	Menu_Print();

	/* loop until space pressed */
	while( !lExitFlag )
	{
		U8 lKey;
		/* wait for key */
		while( !IKBD_GetKbdBytesWaiting());
		lKey = IKBD_PopKbdByte();

		if( eIKBDSCAN_F1 == lKey )
		{
			lSampleIndex = 0;
			Audio_DmaPlaySound(&lSounds[lSampleIndex]);
		}
		else if( eIKBDSCAN_F2 == lKey )
		{
			lSampleIndex = 1;
			Audio_DmaPlaySound(&lSounds[lSampleIndex]);
		}
		else if (eIKBDSCAN_F3 == lKey)
		{
			lSampleIndex = 2;
			Audio_DmaPlaySound(&lSounds[lSampleIndex]);
		}
		else if( eIKBDSCAN_SPACE == lKey )
		{
			lExitFlag = 1;
		}
	}

	/* unload sound samples */
	for (i = 0; i < 3; i++)
	{
		File_UnLoad(lSounds[i].mpSound);
	}
}


/* ################################################################################ */
