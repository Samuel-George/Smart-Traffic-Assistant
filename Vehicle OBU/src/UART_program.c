/*********************************/
/*   Author  : Samuel George     */
/*   Date    : 2 April 2021 	 */
/*   Version : V01				 */
/*********************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"

#include <stdio.h>
#include <math.h>

#define THRESHOLD_TIMEOUT_USART2 800
#define THRESHOLD_TIMEOUT_USART1 6000
#define THRESHOLD_TIMEOUT_USART3 1000000

void  MUSART1_voidInit ( void )
{
	/*  Baud rate  */
	
	#if   UART1_BaudRate == 9600
	{
		// 9600   BRR = 0x341
		MUSART1->BRR = 0x341;
	}
	#elif UART1_BaudRate == 115200
	{
		// 115200 BRR = 0x54
		MUSART1->BRR = 0x45;
	}
	#elif UART1_BaudRate == 19200
	{
		// 19200 BRR = 0x1A1
		MUSART1->BRR = 0x1A1;
	}
	#endif

	SET_BIT ( MUSART1 -> CR1 , 13 );	// Enable USART
	SET_BIT ( MUSART1 -> CR1 , 3  );	// Enable Transmitter
	SET_BIT ( MUSART1 -> CR1 , 2  );	// Enable Receiver

	/* Clear Status  Registers*/
	MUSART1 -> SR = 0;
}

void  MUSART1_voidTransmitString ( u8 arr[   ] )
{
	u8 i = 0 ;
	while( arr[i] != '\0' )
	{
		MUSART1 -> DR = arr[i];
		/*  Check Transmission Completer ( TC ) bit */
		while( GET_BIT ( MUSART1 -> SR , 6 ) == 0 ) ;
		i++;
	}

}


void  MUSART1_voidTransmitChar ( u8 copy_u8char )
{
	MUSART1 -> DR = copy_u8char;

	while( GET_BIT ( MUSART1 -> SR , 6 ) == 0 ) ;

	CLR_BIT(  MUSART1 -> SR , 6  );

}

u8    MUSART1_u8Receive ( u32 Copy_u32TIMEOUT)
{
	u32 timeout = 0;
	
	u8 Loc_u8ReceivedData = 0;
	/*  Bit 5 : RXNE: Read data register not empty if 1 :Received data is ready to be read.  */
	while( ( GET_BIT ( MUSART1 -> SR , 5 ) ) == 0 &&  (timeout < Copy_u32TIMEOUT)  )
	{
		timeout++;

	}
	if (timeout == Copy_u32TIMEOUT)
	{
			Loc_u8ReceivedData = 255;
	}
	else
	{
		Loc_u8ReceivedData = MUSART1 -> DR ;
	}


	return ( (Loc_u8ReceivedData)); // To make sure return just only first 8 bits in reg


}
/*
char String[20];
char * MUSART1_u8ReceiveString ( u8 copy_u8LastChar )
{
	u8 LOC_Iterator = 0 , LOC_u8DataCome ;

	// Save till LastChar
	while( ( LOC_u8DataCome = MUSART1_u8Receive() ) != copy_u8LastChar )
	{
		String[ LOC_Iterator ] = LOC_u8DataCome ;
		LOC_Iterator++;
	}
	String[ LOC_Iterator ] = LOC_u8DataCome ;

	//Receive the rest unneeded data
	while (   MUSART1_u8Receive() != 255  );


	return ( String );
}
*/
void MUSART1_VidClearFlags( void )
{

	/* Clear all flags */
	MUSART1 -> SR = 0;

}


void  MUSART2_voidInit ( void )
{
	/*  Baud rate  */

	#if   UART2_BaudRate == 9600
	{
		// 9600   BRR = 0x341
		MUSART2->BRR = 0x341;
	}
	#elif UART2_BaudRate == 115200
	{
		// 115200 BRR = 0x54
		MUSART2->BRR = 0x45;
	}
	#elif UART2_BaudRate == 19200
	{
		// 19200 BRR = 0x1A1
		MUSART2->BRR = 0x1A1;
	}
	#endif

	SET_BIT ( MUSART2 -> CR1 , 13 );	// Enable USART
	SET_BIT ( MUSART2 -> CR1 , 3  );	// Enable Transmitter
	SET_BIT ( MUSART2 -> CR1 , 2  );	// Enable Receiver

		/* Clear Status  Registers*/
		MUSART2 -> SR = 0;
}

void  MUSART2_voidTransmit ( u8 arr[   ] )
{
	u8 i = 0 ;
	while( arr[i] != '\0' )
	{
		MUSART2 -> DR = arr[i];
		/*  Check Transmission Completer ( TC ) bit */
		while( GET_BIT ( MUSART2 -> SR , 6 ) == 0 ) ;
		i++;
	}

}


void  MUSART2_voidTransmitChar ( u8 copy_u8char )
{
	MUSART2 -> DR = copy_u8char;

	while( GET_BIT ( MUSART2 -> SR , 6 ) == 0 ) ;

	CLR_BIT(  MUSART2 -> SR , 6  );

}


u8    MUSART2_u8Receive ( void )
{

	u16 timeout = 0;

	u8 Loc_u8ReceivedData = 0;
	/*  Bit 5 : RXNE: Read data register not empty if 1 :Received data is ready to be read.*/
	while( ( GET_BIT ( MUSART2 -> SR , 5 ) ) == 0 && ( timeout < THRESHOLD_TIMEOUT_USART2 ))
	{
		timeout++;
	}

	if( timeout == THRESHOLD_TIMEOUT_USART2 )
	{
		Loc_u8ReceivedData = 255;
	}
	else
	{

		Loc_u8ReceivedData = MUSART2 -> DR;
	}

	return Loc_u8ReceivedData;

/*
	u8 Loc_u8ReceivedData = 0;
	/*  Bit 5 : RXNE: Read data register not empty if 1 :Received data is ready to be read.
	while( ( GET_BIT ( MUSART1 -> SR , 5 ) ) == 0 )
	{
		Loc_u8ReceivedData = MUSART1 -> DR;
	}

	return Loc_u8ReceivedData;
*/
}

void  MUSART3_voidInit ( void )
{
	/*  Baud rate  */

	#if   USART3_BaudRate == 9600
	{
		// 9600   BRR = 0x341
		MUSART3->BRR = 0x341;
	}
	#elif USART3_BaudRate == 115200
	{
		// 115200 BRR = 0x54
		MUSART3->BRR = 0x45;
	}
	#elif USART3_BaudRate == 19200
	{
		// 19200 BRR = 0x1A1
		MUSART3->BRR = 0x1A1;
	}
	#endif

	SET_BIT ( MUSART3 -> CR1 , 13 );	// Enable USART
	SET_BIT ( MUSART3 -> CR1 , 3  );	// Enable Transmitter
	SET_BIT ( MUSART3 -> CR1 , 2  );	// Enable Receiver

	/* Clear Status  Registers*/
	MUSART3 -> SR = 0;
}


void  MUSART3_voidTransmit ( u8 arr[   ] )
{
	u8 i = 0 ;
	while( arr[i] != '\0' )
	{
		MUSART3 -> DR = arr[i];
		/*  Check Transmission Completer ( TC ) bit */
		while( GET_BIT ( MUSART3 -> SR , 6 ) == 0 ) ;
		i++;
	}

}


u8    MUSART3_u8Receive ( void )
{
	u16 timeout = 0;

	u8 Loc_u8ReceivedData = 0;
	/*  Bit 5 : RXNE: Read data register not empty if 1 :Received data is ready to be read.  */
	while( ( GET_BIT ( MUSART3 -> SR , 5 ) ) == 0 && ( timeout < THRESHOLD_TIMEOUT_USART3 ))
	{
		timeout++;
	}

	if( timeout == THRESHOLD_TIMEOUT_USART3 )
	{
		Loc_u8ReceivedData = 255;
	}
	else
	{

		Loc_u8ReceivedData = MUSART3 -> DR;
	}

	return Loc_u8ReceivedData;


}



// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.
void ftoa(f64 n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    f64 fpart = n - (f64)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

