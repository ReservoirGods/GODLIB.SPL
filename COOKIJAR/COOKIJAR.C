/*************************************************************************************
 * GodLib Example Progam Suite
 * 
 * Demonstrates cookiejar functionality
 *
 * PINK 01.01.03
 *************************************************************************************
*/

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\GEMDOS\GEMDOS.H>
#include	<GODLIB\COOKIE\COOKIE.H>


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

	if( CookieJar_Exists() )
	{
		if( CookieJar_CookieExists( '_MCH' ) )
		{
			printf( "_MCH value : %lX\n", CookieJar_GetCookieValue( '_MCH' ) );
		}
		else
		{
			printf( "_MCH Cookie not found\n" );
		}
	}
	else
	{
		printf( "No Cookie Jar found\n" );
	}

	GemDos_Cnecin();

	return( 0 );
}


/* ################################################################################ */
