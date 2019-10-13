/*
 * Tmu.c
 *
 *  Created on: 12 Oct 2019
 *      Author: RGB
 */
#include "Tmu.h"
#include "DIO.h"
 TMU_start TMU_Buffer[MAX_NUM_TASKS] ;

uint16 flags[MAX_NUM_TASKS]={0};
uint8 ACTIVE_TASKS = MAX_NUM_TASKS ;

EnmTMUError TMU_Init(const TMU_ConfigType * ConfigPtr) {
	uint8 retvalue = OK;
	uint8 index ;
	for (index=0;index<MAX_NUM_TASKS;index++)
	{
		TMU_Buffer[index].delay_time=0;
		TMU_Buffer[index].state=0;
		TMU_Buffer[index].fun_ptr=NULL;
		TMU_Buffer[index].periodic=0;
	}


	timer_set_cb(flags_func);
	if (0 == ConfigPtr->Timer_id) {
		TIMER_cnfg_arr[ConfigPtr->Timer_id].used=USED;
	} else {
		retvalue = NOK;
	}
	return retvalue;
}

EnmTMUError TMU_Start_Timer (uint16 delay_time , uint8 periodic , void (*fun_ptr)(void))
 {
	uint8 retvalue =OK;
	uint8 index = 0;
	for (index=0; index<ACTIVE_TASKS;index++)
	{
		if(TMU_Buffer[index].state==0)
		{
			TMU_Buffer[index].delay_time=delay_time;
			TMU_Buffer[index].periodic=periodic;
			TMU_Buffer[index].fun_ptr=fun_ptr;
			TMU_Buffer[index].state=1;

		}
		else
		{
		}

	}

		return retvalue ;

 }



EnmTMUError  TMU_Dispatch ()
 { uint8 retvalue =OK;
	 uint8 index ;
 for (index= 0 ; index<ACTIVE_TASKS;index++)
 {

 if(flags[index] ==TMU_Buffer[index].delay_time)
	{flags[index]=0;


	timer_set_cb(TMU_Buffer[index].fun_ptr);
	}


 }

	 return retvalue ;
 }

  EnmTMUError TMU_Stop_Timer ( void (*fun_ptr)(void))
  {
	  uint8 retvalue =OK;
	  uint8 index;

	  for (index=0;index<ACTIVE_TASKS;index++)
	  {
		  if (TMU_Buffer[index].fun_ptr==fun_ptr)
		  {  TMU_Buffer[index]=TMU_Buffer[ACTIVE_TASKS-1];
		  flags[index]=flags[ACTIVE_TASKS-1];

		  ACTIVE_TASKS--;
		  break ;
		  }
		  else
		  {
			  retvalue=NOK;
		  }

	  }



		return retvalue ;

  }

  void flags_func()
  { uint8 index ;
	  for(index=0;index<ACTIVE_TASKS;index++)
	  {
	  flags[index]++;

	  }

  }

