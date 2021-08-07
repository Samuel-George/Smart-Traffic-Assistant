/**********************************************/
/*  	 	Author : Samuel George 			  */
/*   	 	Date   : 7 April 2021			  */
/*			Version: V01					  */
/**********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"

#include "GPS_config.h"
#include "GPS_private.h"
#include "GPS_interface.h"

#include<stdlib.h>
#include<math.h>





void HGPS_voidGetLocation( f64 * Longitude , f64 * Latitude )
{
	u8 Local_u8Response[100] = {0} ;
	char Long_s[10] = {0};
	char Lati_s[11] = {0};
	u8 i  = 0;
	u8 i2 = 0;
	u8 Dummy= 0 ;
	u8 Result = 0;
	

	while ( Result == 0)
	{
		while ( MUSART2_u8Receive() == '$')
		{
			if ( MUSART2_u8Receive() == 'G')
			{
				if ( MUSART2_u8Receive() == 'N' )
				{
					if ( MUSART2_u8Receive() == 'R' )
					{
						if ( MUSART2_u8Receive() == 'M' )
						{
							if ( MUSART2_u8Receive() == 'C' )
							{
								for ( i = 0 ; i <= 10 ; i++ )
								{
									MUSART2_u8Receive();
								}
								if ( MUSART2_u8Receive() == 'A' )
								{
									MUSART2_u8Receive();
									for ( i = 0 ; i < 10 ; i++ )	 Long_s[i] = MUSART2_u8Receive() ;
									for ( i = 0 ; i < 3  ; i++ ) 		 MUSART2_u8Receive() ;
								    for ( i = 0 ; i <= 10 ; i++ )	 Lati_s[i] = MUSART2_u8Receive() ;
									f64 Long = atof(Long_s);
									f64 Lati = atof(Lati_s);
									*Longitude = HGPS_f64ConvertLocation(Long);   // f64 to be more accurate or f32 to be approximated
									*Latitude  = HGPS_f64ConvertLocation(Lati);   // f64 to be more accurate or f32 to be approximated
									Result = 1;
									break;

								}
							}

						}

					}
				}

			}
		}
	}
	/*

		i2 = 0;
		Dummy = 0;
		while( )
		{
			Dummy = MUSART1_u8Receive();
			Local_u8Response[i2] = Dummy;
			i2++;
		}

		if (   Local_u8Response[0] == '$' &&  Local_u8Response[1] == 'G' && Local_u8Response[2] == 'N' && Local_u8Response[3] == 'R' && Local_u8Response[4] == 'M' && Local_u8Response[5] == 'C' && Local_u8Response[17] == 'A' )
		{
			for ( i = 0 ; i < 10 ; i++ )	 Long_s[i] = Local_u8Response[19+i] ;
			for ( i = 0 ; i <= 10 ; i++ )	 Lati_s[i] = Local_u8Response[32+i] ;
			f64 Long = atof(Long_s);
			f64 Lati = atof(Lati_s);
			*Longitude = HGPS_f64ConvertLocation(Long);   // f64 to be more accurate or f32 to be approximated
			*Latitude  = HGPS_f64ConvertLocation(Lati);   // f64 to be more accurate or f32 to be approximated
			Result = 1;
		}

		else Result = 0 ;

	}
	*/
}


f64  HGPS_f64ConvertLocation ( f64 Copy_f64Location )
{
	 f64 degrees = floor(Copy_f64Location / 100);
	 f64 minutes = Copy_f64Location - (100 * degrees);
	 minutes /= 60;
	 degrees += minutes;
	 return degrees;

}

