/*********************************************/
/*  AUTHOR  	:	Samuel George			 */
/*  Date 		:	8/14/2020				 */
/* 	Version		:	01						 */
/*  Description	:	GPIO REGISTERS			 */
/*********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"

void MGPIO_voidSetPinDirection(u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Mode)
{
	switch (copy_u8PORT)
	{
		case GPIOA :
		{
					if(copy_u8PIN <= 7)
					{
						MGPIOA->CRL &= ~ ((0b1111)<< (copy_u8PIN * 4));
						MGPIOA->CRL |=  ((copy_u8Mode)<< (copy_u8PIN * 4));
					}
					else if(copy_u8PIN <= 15)
					{
						copy_u8PIN = copy_u8PIN - 8 ;
						MGPIOA->CRH &= ~ ((0b1111)<< (copy_u8PIN * 4));
						MGPIOA->CRH |=  ((copy_u8Mode)<< (copy_u8PIN * 4));
					}
					break;
		}
		case GPIOB :
		{
					if(copy_u8PIN <= 7)
					{
						MGPIOB->CRL &= ~ ((0b1111)<< (copy_u8PIN * 4));
						MGPIOB->CRL |=  ((copy_u8Mode)<< (copy_u8PIN * 4));
					}
					else if(copy_u8PIN <= 15)
					{
						copy_u8PIN = copy_u8PIN - 8 ;
						MGPIOB->CRH &= ~ ((0b1111)<< (copy_u8PIN * 4));
						MGPIOB->CRH |=   ((copy_u8Mode)<< (copy_u8PIN * 4));
					}
					break;
		}
		case GPIOC :
		{
					if(copy_u8PIN <= 7)
					{
						MGPIOC->CRL &= ~ ((0b1111)<< (copy_u8PIN * 4));
						MGPIOC->CRL |=   ((copy_u8Mode)<< (copy_u8PIN * 4));
					}
					else if(copy_u8PIN <= 15)
					{
						copy_u8PIN = copy_u8PIN - 8 ;
						MGPIOC->CRH &= ~ ((0b1111)<< (copy_u8PIN * 4));
						MGPIOC->CRH |=   ((copy_u8Mode)<< (copy_u8PIN * 4));
					}
					break;
		}
		default :
					break;
	}
}

void MGPIO_voidSetPinValue(u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Value)
{
	switch(copy_u8PORT)
	{
		case GPIOA :
					if(copy_u8Value == HIGH)
					{
						SET_BIT(MGPIOA->ODR , copy_u8PIN);
					}
					else if(copy_u8Value == LOW)
					{
						CLR_BIT(MGPIOA->ODR , copy_u8PIN);
					}
					break;
		case GPIOB :
					if(copy_u8Value == HIGH)
					{
						SET_BIT(MGPIOB->ODR , copy_u8PIN);
					}
					else if(copy_u8Value == LOW)
					{
						CLR_BIT(MGPIOB->ODR , copy_u8PIN);
					}
					break;
		case GPIOC :
					if(copy_u8Value == HIGH)
					{
						SET_BIT(MGPIOC->ODR , copy_u8PIN);
					}
					else if(copy_u8Value == LOW)
					{
						CLR_BIT(MGPIOC->ODR , copy_u8PIN);
					}
					break;
		default :   break;				
	}
}

u8 MGPIO_u8GetPinValue(u8 copy_u8PORT , u8 copy_u8PIN )
{
	u8 LOC_u8Result = 0;
	
	switch(copy_u8PORT)
	{
		case GPIOA :  
					LOC_u8Result = GET_BIT(MGPIOA->IDR , copy_u8PIN);
					break;
		case GPIOB :
					LOC_u8Result = GET_BIT(MGPIOB->IDR , copy_u8PIN);
					break;
		case GPIOC :
					LOC_u8Result = GET_BIT(MGPIOC->IDR , copy_u8PIN);
					break;
		default :   break;				
	}
	return LOC_u8Result;
}

void MGPIO_voidSetPortDirection(u8 copy_u8PORT ,u8 copy_u8PortPosition , u8 copy_u8Mode)
{
	switch (copy_u8PORT)
	{
		case GPIOA :
		{
			if      ( copy_u8PortPosition == LOW  )   MGPIOA->CRL = ( 0x11111111 * copy_u8Mode );
			else if ( copy_u8PortPosition == HIGH )   MGPIOA->CRH = ( 0x11111111 * copy_u8Mode );
			break;
		}
		case GPIOB :
		{
			if      ( copy_u8PortPosition == LOW  )   MGPIOB->CRL = ( 0x11111111 * copy_u8Mode );
			else if ( copy_u8PortPosition == HIGH )   MGPIOB->CRH = ( 0x11111111 * copy_u8Mode );
			break;
		}
		case GPIOC :
		{
			if      ( copy_u8PortPosition == LOW  )   MGPIOC->CRL = ( 0x11111111 * copy_u8Mode );
			else if ( copy_u8PortPosition == HIGH )   MGPIOC->CRH = ( 0x11111111 * copy_u8Mode );
			break;
		}
		default : break;
	}
}

void MGPIO_voidSetPortValue( u8 copy_u8PORT , u8 copy_u8PortPosition  ,u16 copy_u8Value )
{
	switch (copy_u8PORT)
	{
		case GPIOA :
		{
			if      ( copy_u8PortPosition == LOW  )    MGPIOA->ODR = ( MGPIOA->ODR & 0xFF00 ) | ( (u8) copy_u8Value  ) ;
			else if ( copy_u8PortPosition == HIGH )    MGPIOA->ODR = ( MGPIOA->ODR & 0x00FF ) | (      copy_u8Value  ) ;
			break;                                               
		}                                                        
		case GPIOB :                                             
		{                                                        
			if      ( copy_u8PortPosition == LOW  )    MGPIOB->ODR = ( MGPIOB->ODR & 0xFF00 ) | ( (u8) copy_u8Value  ) ;
			else if ( copy_u8PortPosition == HIGH )    MGPIOB->ODR = ( MGPIOB->ODR & 0x00FF ) | (      copy_u8Value  ) ;
			break;                                                       
		}                                                                
		case GPIOC :                                                     
		{                                                                
			if      ( copy_u8PortPosition == LOW  )    MGPIOC->ODR = ( MGPIOC->ODR & 0xFF00 ) | ( (u8)  copy_u8Value ) ;
			else if ( copy_u8PortPosition == HIGH )    MGPIOC->ODR = ( MGPIOC->ODR & 0x00FF ) | (       copy_u8Value ) ;
			break;
		}
		default : break;
	}				
}

u16 MGPIO_u8GetPortValue( u8 copy_u8PORT , u8 copy_u8PortPosition )
{
    u16 LOC_u16Result = 0;

	switch( copy_u8PORT )
	{

	case GPIOA:

		LOC_u16Result = MGPIOA->IDR;
		if      ( copy_u8PortPosition == LOW  )  LOC_u16Result &= 0x00FF ;
		else if ( copy_u8PortPosition == HIGH )  LOC_u16Result &= 0xFF00 ;

		break;
	case GPIOB:

		LOC_u16Result = MGPIOB->IDR;
		if      ( copy_u8PortPosition == LOW  )  LOC_u16Result &= 0x00FF ;
		else if ( copy_u8PortPosition == HIGH )  LOC_u16Result &= 0xFF00 ;

		break;
	case GPIOC:

		LOC_u16Result = MGPIOC->IDR;
		if      ( copy_u8PortPosition == LOW  )  LOC_u16Result &= 0x00FF ;
		else if ( copy_u8PortPosition == HIGH )  LOC_u16Result &= 0xFF00 ;

		break;

	}

	return LOC_u16Result ;
	
}
