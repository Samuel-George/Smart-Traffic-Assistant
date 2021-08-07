#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include"STK_private.h"
#include"STK_config.h"
#include"STK_interface.h"

#include"delay_interface.h"

void _delay_ms 	( u32 Copy_u32Time )
{
	MSTK_voidInit ();
	
	MSTK_voidSetBusyWait ( 1000 * Copy_u32Time );
	
}
void _delay_us 	( u32 Copy_u32Time )
{
	MSTK_voidInit ();
	
	MSTK_voidSetBusyWait ( Copy_u32Time );
	
	
}
