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
	DIO_init();
	TMU_Init(&Tmu_init_struct);
	TMU_Start_Timer(500,1,LED_5);
	TMU_Start_Timer(1000,1,LED_12);
	TMU_Start_Timer(800,1,LED_8);

	REG_SREG |=(1<<7);


while(1)
	{
	TMU_Dispatch();
	}

}
