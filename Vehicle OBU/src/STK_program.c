/***************************************/
/* Author   : SamuelGeorge			   */
/* Version	: V01					   */
/* Date 	: 8 August 2020			   */
/***************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include"STK_private.h"
#include"STK_config.h"
#include"STK_interface.h"


void (* MSTK_CallBack) (void);

void MSTK_Handler (void)
{
	MSTK_CallBack();
}

void MSTK_voidInit (void)
{
	// Choose CLKSOURCE 
	#if 	CLKSOURCE ==  AHB
				SET_BIT (STK->CTRL,2);
	#elif CLKSOURCE ==  AHB/8
				CLR_BIT (STK->CTRL,2);
	#else
		#warning " Wrong Clock SOURCE  Configuration Choice "			
	#endif
	
	// Disable STK 
	#if     MSTK_ENABLE == DisableCounter
				CLR_BIT (STK->CTRL,0);
	#elif   MSTK_ENABLE == EnableCounter
				SET_BIT (STK->CTRL,0);
	#else
		#warning " Wrong Configuration Choice "			
	#endif
	
	// Disable STK INT
	#if     MSTK_INT == TICKINT_Enable
				SET_BIT (STK->CTRL,1);
	#elif MSTK_INT == TICKINT_Disable
				CLR_BIT (STK->CTRL,1);
	#else
		#warning " Wrong Configuration Choice "			
	#endif
	
	
}

void MSTK_voidSetBusyWait 		( u32 Copy_u32CounterTicks )
{
	// CLKSOURCE = AHB/8 = Proccesor Clock /8 = 8MHZ/8 = 1 MHZ , T_CLK = 1 us for each count

	// Load Reload Value
	STK->LOAD = Copy_u32CounterTicks ;
	
	// Clear Value Register
	STK->VAL  = 0;

	// Enable STK
	SET_BIT( STK->CTRL , 0);
	
	// Polling , while flag == 0
	while ( GET_BIT (STK->CTRL,16) == 0 );
}
void MSTK_voidSetIntervalSingle ( u32 Copy_u32CounterTicks , void (* Copy_ptr)(void) )
{
	// Load Reload Value
	STK->LOAD = Copy_u32CounterTicks ;
	
	// Clear Value Register
	STK->VAL  = 0;

	// Enable STK
	SET_BIT( STK->CTRL , 0);
	
	// Enable STK INT
	SET_BIT( STK->CTRL , 1);
	
	MSTK_CallBack = Copy_ptr;
	
}


