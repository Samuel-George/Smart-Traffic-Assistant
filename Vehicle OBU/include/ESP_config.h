/**********************************************/
/*  	 	Author : Samuel George 			  */
/*   	 	Date   : 7 April 2021			  */
/*			Version: V01					  */
/**********************************************/

#ifndef	ESP_CONFIG_H
#define ESP_CONFIG_H


/*define recieving timout for each command that if it exceeded it means no more data*/
/*It varies depending on the router and server and also Clock freq, you'll need to try it*/

#define RST_TIMEOUT			400
#define ECHO_TIMEOUT		800
#define MODE_TIMEOUT		300
#define ROUTER_TIMEOUT		900000
#define SERVER_TIMEOUT		6000
#define PREREQUEST_TIMEOUT	500
#define REQUEST_TIMEOUT		300000

//Server 6000
//RE 300000


#endif
