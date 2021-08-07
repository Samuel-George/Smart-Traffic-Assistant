/**********************************************/
/*  	 	Author : Samuel George 			  */
/*   	 	Date   : 7 April 2021			  */
/*			Version: V01					  */
/**********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "GPIO_interface.h"
#include "string.h"
#include "delay_interface.h"

#include "ESP_interface.h"
#include "ESP_config.h"
#include "ESP_private.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void HESP_voidInit(void)
{
	// Close GSM's Response Echo
	MUSART1_voidTransmitString((u8*)"ATE0\r");
}



u8 u8EspValidateCmd(u32 copy_u32TIMEOUT)
{
	u8 Local_u8Response[100] = {0} ; 
	u8 i = 0;
	u8 k = 0;
	u8 Dummy  = 0;
	u8 Result = 0;
	

	for(u8 i = 0; i < 100; i++)
	{
		Local_u8Response[i] = 0;
	}


	while( Dummy != 255 )
	{
		Dummy = MUSART1_u8Receive(copy_u32TIMEOUT);
		Local_u8Response[i] = Dummy;
		i++;
	}


		/* Check  if OK Received */
		//char *r="ATE0\r\r\n\r\nOK\r\n";
		k = 0 ;
		while (  k<i-1)
		{
			if ( (Local_u8Response[k] == 'O' && Local_u8Response[k+1] == 'K' ) || (Local_u8Response[k] == 'W' && Local_u8Response[k+1] == 'I' ))
			{
			Result = 1 ;
			break;
			}
			k++;
		}

	return Result;
	
}




void HESP_voidConnectIP( u8 IP [] )
{
	u8 Local_u8Result = 0;
	while ( Local_u8Result == 0 )
	{
		/*    AT+CIPSTART="TCP","IP","80"   */

		MUSART1_voidTransmitString((u8*)"AT+CIPSTART=\"TCP\",\"");
		MUSART1_voidTransmitString( IP );
		MUSART1_voidTransmitString((u8*)"\",80\r");
		//_delay_ms(2000);
		/* Check Response : CONNECTED    OK */

		Local_u8Result = u8EspValidateIPCmd(SERVER_TIMEOUT);

	}

}


u8 HESP_voidGetData(u8 Web[] , u8 Copy_u8arrLength[] )
{
	u8 timeout=0;
	u8 Local_u8Result = 0;
	//while ( Local_u8Result == 0 && timeout!=10)
	//{
		/*    AT+CIPSEND=41   */

		MUSART1_voidTransmitString((u8*)"AT+CIPSEND=");
		MUSART1_voidTransmitString( Copy_u8arrLength );
		MUSART1_voidTransmitString((u8*)"\r");
		_delay_ms(300);
		/* Check Response : CONNECTED    OK */
		//Local_u8Result = u8EspValidateCmd(PREREQUEST_TIMEOUT);
		//timeout++;
	//}

	//if ( timeout == 10 ) return 2;

	//Local_u8Result = 2;
	//while ( Local_u8Result == 2 )
	//{
		MUSART1_voidTransmitString( (u8 *) "GET https://" );
		MUSART1_voidTransmitString( (u8 *) Web );
		MUSART1_voidTransmitString( (u8 *) "-2" );
		MUSART1_voidTransmitString( (u8 *) "\r\n" );

		Local_u8Result = u8EspValidateReqCmd(REQUEST_TIMEOUT);
	//}

	return Local_u8Result;
}


u8 HESP_voidTrafficData(u8 Copy_u8arrLength[] )
{
	u8 timeout=0;
	u8 Local_u8Result = 0;
	//while ( Local_u8Result == 0 && timeout!=10)
	//{
		/*    AT+CIPSEND=41   */

		MUSART1_voidTransmitString((u8*)"AT+CIPSEND=");
		MUSART1_voidTransmitString( Copy_u8arrLength );
		MUSART1_voidTransmitString((u8*)"\r");
		_delay_ms(300);
		/* Check Response : CONNECTED    OK */
		//Local_u8Result = u8EspValidateCmd(PREREQUEST_TIMEOUT);
		//timeout++;
	//}

	//if ( timeout == 10 ) return 2;

	//Local_u8Result = 2;
	//while ( Local_u8Result == 2 )
	//{
		MUSART1_voidTransmitString( (u8 *) "GET https://traffica.herokuapp.com/navigation/gsm" );
		MUSART1_voidTransmitString( (u8 *) "\r\n" );

		Local_u8Result = u8EspValidateTrafficReqCmd(REQUEST_TIMEOUT);
	//}

	return Local_u8Result;
}

u8 u8EspValidateReqCmd(u32 copy_u32TIMEOUT)
{
	u8 Local_u8Response[100] = {0} ;
	u8 i = 0;
	u8 k = 0;
	u8 Dummy  = 0;
	u8 Result = 0;


	while( Dummy != 255 )
	{
		Dummy = MUSART1_u8Receive(copy_u32TIMEOUT);
		Local_u8Response[i] = Dummy;
		i++;
	}
	u8 r=0;
	k = 0 ;
	while (  k<i-1)
	{
			if ( Local_u8Response[k] == 'O' &&  Local_u8Response[k+1] == 'K')
			{
				r++;
				if (r==2)
				{
					Result = 1 ;
					break;
				}
			}
			k++;
	}

	return Result;
}

u8 u8EspValidateTrafficReqCmd(u32 copy_u32TIMEOUT)
{
	u8 T_u8Response[150] = {0} ;
	u8 Traffic_u8Response[100] = "Dawaran " ;
	u8 i = 0;
	u8 k = 0;
	u8 Dummy  = 0;
	u8 Result = 0;
	u8 T_i=0;
	u8 Get_D=0;
	u8 time[3];
	u8 G_f=0,R_f=0,Y_f=0;

	while( Dummy != 255 )
	{
		Dummy = MUSART1_u8Receive(copy_u32TIMEOUT);
		T_u8Response[i] = Dummy;
		i++;
	}

	k = 0 ;
	while (  k<i-1)
	{
			if ( T_u8Response[k] == 'a' &&  T_u8Response[k+1] == 't' && Get_D==0)
			{
				while (T_u8Response[k+3+T_i] != ' ')
				{
					Traffic_u8Response[8+T_i]=T_u8Response[k+3+T_i];
					T_i++;
				}
				Get_D=1;
			}

			if ( Get_D==1)
			{
				if ( T_u8Response[k] == 'G' )
				{
					G_f=1;
				}
				else if ( T_u8Response[k] == 'R' )
				{
					R_f=1;
				}
				else if ( T_u8Response[k] == 'Y' )
				{
					Y_f=1;
				}
	/*
				if (Local_u8Response[k] == 'i' &&  Local_u8Response[k+1] == 'm' && Local_u8Response[k+2] == 'e')
				{
					time[0]=Local_u8Response[k+6];
					time[1]=Local_u8Response[k+7];
					strcat(Traffic_u8Response,time);
				}
	*/
			}


			k++;
	}


	if ( G_f == 1) strcat(Traffic_u8Response," Green ");
	else if ( Y_f == 1) strcat(Traffic_u8Response," Yellow ");
	else if ( R_f == 1) strcat(Traffic_u8Response," Red ");


	strcat(Traffic_u8Response,"20");


	//_delay_ms(500);
	//MUSART3_voidTransmit(Traffic_u8Response);

	if (Get_D == 1)
		{
			MUSART3_voidTransmit(Traffic_u8Response);
			return 1;
		}
	return 0;
}



u8 u8EspValidateIPCmd  (u32 copy_u32TIMEOUT)
{
	u8 Local_u8Response[100] = {0} ;
	u8 i = 0;
	u8 k = 0;
	u8 Dummy  = 0;
	u8 Result = 0;



	while( Dummy != 255 )
	{
		Dummy = MUSART1_u8Receive(copy_u32TIMEOUT);
		Local_u8Response[i] = Dummy;
		i++;
	}

		k = 0 ;
		while (  k<i-1)
		{
			if ( ( Local_u8Response[k] == 'O' && Local_u8Response[k+1] == 'K' ) || (Local_u8Response[k] == 'A' && Local_u8Response[k+1] == 'L' && Local_u8Response[k+2] == 'R') )
			{
			Result = 1 ;
			break;
			}
			k++;
		}

		return Result;

}

u8 u8EspValidateWifiCmd  (u32 copy_u32TIMEOUT)
{
	u8 Local_u8Response[100] = {0} ;
	u8 i = 0;
	u8 k = 0;
	u8 Dummy  = 0;
	u8 Result = 0;


	for(u8 i = 0; i < 100; i++)
	{
		Local_u8Response[i] = 0;
	}


	while( Dummy != 255 )
	{
		Dummy = MUSART1_u8Receive(copy_u32TIMEOUT);
		Local_u8Response[i] = Dummy;
		i++;
	}


		/* Check  if OK Received */
		//char *r="ATE0\r\r\n\r\nOK\r\n";
		k = 0 ;
		u8 r=0;
		while (  k<i-1)
		{
			if ( Local_u8Response[k] == 'O' && Local_u8Response[k+1] == 'K' )
			{
				r++;
				if (r==2)
				{
					Result = 1 ;
					break;
				}
			k++;
			}
		}
	return Result;
}

