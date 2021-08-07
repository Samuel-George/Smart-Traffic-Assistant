/***************************************/
/* Author   : SamuelGeorge			   */
/* Version	: V01					   */
/* Date 	: 8 August 2020			   */
/***************************************/
	
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"


void MRCC_voidInitSysClock(void)
{
	#if    RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
		RCC->CR   = 0x00010000;  /* Enable HSE with no bypass */
 		RCC->CFGR = 0x00000001;
		
	#elif  RCC_CLOCK_TYPE == RCC_HSE_RC
		RCC->CR   = 0x00050000;  /* Enable HSE with bypass */
		RCC->CFGR = 0x00000001;
		
	#elif  RCC_CLOCK_TYPE == RCC_HSI
		RCC->CR   = 0x00000081;  /* Enable HSI + Trimming = 0 */
		RCC->CFGR = 0x00000000;
		
	#elif  RCC_CLOCK_TYPE == PLL
		#if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
		
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
		
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
		
		#endif
	
	#else
		#error("You chosed Wrong Clock type")
	#endif
	
}

void MRCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if (Copy_u8PerId <= 31 )
	{
		switch (Copy_u8BusId)
		{
			case RCC_AHB  :	SET_BIT(RCC->AHBENR  , Copy_u8PerId); break;
			case RCC_APB1 :	SET_BIT(RCC->APB1ENR , Copy_u8PerId); break;
			case RCC_APB2 : SET_BIT(RCC->APB2ENR , Copy_u8PerId); break;
		}
	}
	else
	{
		/*Return Error */
	}
}




void MRCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if (Copy_u8PerId <= 31 )
	{
		switch (Copy_u8BusId)
		{
			case RCC_AHB  :	CLR_BIT(RCC->AHBENR  , Copy_u8PerId); break;
			case RCC_APB1 :	CLR_BIT(RCC->APB1ENR , Copy_u8PerId); break;
			case RCC_APB2 : CLR_BIT(RCC->APB2ENR , Copy_u8PerId); break;
		}
	}
	else
	{
		/*Return Error */
	}
}
