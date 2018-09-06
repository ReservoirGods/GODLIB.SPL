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

#include	<GODLIB\AUDIO\SSD.H>
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
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Hardware_DeInit( void )
* ACTION   : Hardware_DeInit
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Hardware_DeInit( void )
{
	IKBD_DeInit();
	Vbl_DeInit();
	System_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_Loop( void )
* ACTION   : Test_Loop
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Menu_Print( U8 aTuneIndex )
{
	/* encode screen clear and cursor off into string using VT-52 codes */
	char *	lpString = "\033E\033f-GodLib Music Sample-\n\r";
	char *	lpT1 = "*[F1] - TUNE 1\033q\n\r";
	char *	lpT2 = " [F2] - TUNE 2\033q\n\r";
	char *	lpQ = " [Space] - Quit\n\r";

	if( aTuneIndex )
	{
		lpT1[0] = ' ';
		lpT2[0] = '*';
	}
	else
	{
		lpT1[0] = '*';
		lpT2[0] = ' ';		
	}

	/* print information */
	GemDos_Cconws( lpString );
	if( !aTuneIndex )
		GemDos_Cconws( "\033p");
	GemDos_Cconws( lpT1 );
	if( aTuneIndex )
		GemDos_Cconws( "\033p");
	GemDos_Cconws( lpT2 );
	GemDos_Cconws( lpQ );

}

/*-----------------------------------------------------------------------------------*
* FUNCTION : Test_Loop( void )
* ACTION   : Test_Loop
* CREATION : 11.08.2018 PNK
*-----------------------------------------------------------------------------------*/

void	Test_Loop( void )
{
	void * lpVoiceSet;
	void * lpTunes[ 2 ];
	U8	lTuneIndex = 0;
	U8	lExitFlag = 0;

	/* initialise Sid Sound Designer player */
	Ssd_Init();

	/* load voice set and two tunes */
	lpVoiceSet = File_Load("CHU.TVS");
	lpTunes[ 0 ]= File_Load("CHOP_1.TRI");
	lpTunes[ 1 ]= File_Load("CHOP_2.TRI");


	/* start playing back tune 0 */
	Ssd_Start( lpVoiceSet, lpTunes[0]);

	/* loop until space pressed */
	while( !lExitFlag )
	{
		U8 lKey;

		Menu_Print( lTuneIndex );

		/* wait for key */
		while( !IKBD_GetKbdBytesWaiting());
		lKey = IKBD_PopKbdByte();

		if( eIKBDSCAN_F1 == lKey )
		{
			/* stop old tune and play tune 0 */
			Ssd_Stop();
			Ssd_Start( lpVoiceSet, lpTunes[0]);

			lTuneIndex = 0;
		}
		else if( eIKBDSCAN_F2 == lKey )
		{
			/* stop old tune and play tune 1 */
			Ssd_Stop();
			Ssd_Start( lpVoiceSet, lpTunes[1]);

			lTuneIndex = 1;
		}
		else if( eIKBDSCAN_SPACE == lKey )
		{
			lExitFlag = 1;
		}
	}

	/* stop sid sound designer playback */
	Ssd_Stop();

	/* unload tunes and voiceset */
	File_UnLoad(lpTunes[ 1 ]);
	File_UnLoad(lpTunes[ 0 ]);
	File_UnLoad(lpVoiceSet);

	/* de-initialise sid sound designer */
	Ssd_DeInit();
}





/* ################################################################################ */
