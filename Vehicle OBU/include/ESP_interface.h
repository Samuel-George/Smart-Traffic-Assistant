/**********************************************/
/*  	 	Author : Samuel George 			  */
/*   	 	Date   : 7 April 2021			  */
/*			Version: V01					  */
/**********************************************/

#ifndef	ESP_INTERFACE_H
#define ESP_INTERFACE_H

void HESP_voidInit(void);

void HESP_voidConnectWifi( u8 Username_arr[] , u8 Pass_arr[] );
void HESP_voidConnectIP( u8 IP [] );
u8   HESP_voidGetData(u8 Web[] , u8 Copy_u8arrLength[] );
u8 HESP_voidTrafficData(u8 Copy_u8arrLength[] );
u8 u8EspValidateTrafficReqCmd(u32 copy_u32TIMEOUT);




#endif
