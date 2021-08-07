#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "delay_interface.h"
#include "UART_interface.h"
#include "ESP_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (void)
{

	// RCC Init
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock( RCC_APB2  , RCC_GPIOA  );
	MRCC_voidEnableClock( RCC_APB2  , RCC_GPIOB  );

	MRCC_voidEnableClock( RCC_APB2  , RCC_USART1 );
	MRCC_voidEnableClock( RCC_APB1  , RCC_USART2 );
	MRCC_voidEnableClock( RCC_APB1  , RCC_USART3 );


	// USART 1 Init

	MUSART1_voidInit();
	MGPIO_voidSetPinDirection( GPIOA , PIN9  , OUTPUT_SPEED_50MHZ_AFPP );	// A9 TX
	MGPIO_voidSetPinDirection( GPIOA , PIN10 , INPUT_FLOATING 		  );	// A10 RX

	// USART 2 Init

	MUSART2_voidInit() ;
	MGPIO_voidSetPinDirection( GPIOA , PIN2  , OUTPUT_SPEED_50MHZ_AFPP );  // A2  TX out 50 MHz
    MGPIO_voidSetPinDirection( GPIOA , PIN3  , INPUT_FLOATING 		   );  // A3 RX In

    // USART 3 Init

    MUSART3_voidInit() ;
	MGPIO_voidSetPinDirection( GPIOB , PIN10  , OUTPUT_SPEED_50MHZ_AFPP );  // B10  TX out 50 MHz
    MGPIO_voidSetPinDirection( GPIOB , PIN11  , INPUT_FLOATING 		   );   // B11  RX In

    // GSM Init
    HESP_voidInit();
	u8 ServerData ;


    // GPS Init
	f64 Longitude, Latitude;
	u8 Longitude_string[10] , Latitude_string [10];

	// Tracking and Traffic light use cases
	while(1)
	{

		u8 GetReq[58] = "traffica.herokuapp.com/navigation/";

		// Get Location From GPS
		HGPS_voidGetLocation( &Longitude , &Latitude);

		// float to string
		ftoa( Longitude , Longitude_string , 7 );
		ftoa( Latitude  , Latitude_string  , 7 );

		// Add Loc to GetReq

		strcat(GetReq,Longitude_string);
		strcat(GetReq,"-");
		strcat(GetReq,Latitude_string);

		// Send Location To Website
		ServerData = 0;
		while(ServerData == 0)
		{
			HESP_voidConnectIP((u8*)"traffica.herokuapp.com");
			ServerData=HESP_voidGetData(GetReq, (u8*)"71");
		}


		// Get Traffic light
		ServerData = 0;
		while(ServerData == 0)
		{
			HESP_voidConnectIP((u8*)"traffica.herokuapp.com");
			ServerData=HESP_voidTrafficData((u8*)"51");
		}


	}



	return 0;
}
