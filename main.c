/*
 * main.c
 *
 *  Created on: 12 Oct 2019
 *      Author: RGB
 */
#include "Tmu.h"
#include "app.h"
void main (void)
{
	DIO_init();/*DIO INIT*/
	TMU_Init(&Tmu_init_struct);/*Initial stucture for tmu*/
	TMU_Start_Timer(500,Periodic,LED_1);
	TMU_Start_Timer(1000,One_shot,LED_2);/*on shot function*/
	TMU_Start_Timer(800,Periodic,LED_3);
	uint8 Stop_btn,Start_btn ;/* two buttons to start or stop  */

	REG_SREG |=(1<<7);
/*3 functions middle one is a oneshot
 * 2 buttons to stop and restart task one*/

while(1)
	{
	TMU_Dispatch();
	DIO_read_pin_value(PORT_D,PIN1,&Stop_btn);
	DIO_read_pin_value(PORT_D,PIN2,&Start_btn);
	if (Stop_btn==0)/*stop task1*/
	{
		TMU_Stop_Timer(LED_1);
	}
	if(Start_btn==0)/*start new task*/
	{
	TMU_Start_Timer(200,Periodic,LED_4);

	}

	}

}
