/*
 * Tmu.c
 *
 *  Created on: 12 Oct 2019
 *      Author: RGB
 */
#include "Tmu.h"
#include "DIO.h"
TMU_start TMU_Buffer[MAX_NUM_TASKS]; /*Buffer(array of structure*/
uint32 flags[MAX_NUM_TASKS] = { 0 }; /*array of flags */
uint8 ACTIVE_TASKS = 0; /*indication to last active tasks*/
uint16 global_resolution = 0; /*global variable storing the resolution*/
uint8 ISR_Flag;/*flag to indicate if the isr is done*/

/*init function that takes pointer to structure of init values
 * initializing buffer , assigning resolution , calling timer init */
EnmTMUError TMU_Init(const TMU_ConfigType * ConfigPtr) {
	uint8 retvalue = OK;
	uint8 index;
	if (ConfigPtr == NULL)
	{
		retvalue = NOK;
	}
	else
	{
		for (index = 0; index < MAX_NUM_TASKS; index++) {
			TMU_Buffer[index].delay_time = 0;
			TMU_Buffer[index].state = 0;
			TMU_Buffer[index].fun_ptr = NULL;
			TMU_Buffer[index].periodic = 0;
		}

		timer_set_cb(flags_func);
		if (0 == ConfigPtr->Timer_id) {
			TIMER_cnfg_arr[ConfigPtr->Timer_id].used = USED;
		} else {
			retvalue = NOK;
		}
		global_resolution = ConfigPtr->Resolution;
		Timer_init();
	}
	return retvalue;

}

/* function that takes delay_time and periodicity of task , task name and assigning it to the buffer */
EnmTMUError TMU_Start_Timer(uint16 delay_time, uint8 periodic,void (*fun_ptr)(void))
{
	uint8 retvalue = OK;

	if (ACTIVE_TASKS < MAX_NUM_TASKS) /*if buffer is not full*/
	{
		TMU_Buffer[ACTIVE_TASKS].delay_time = delay_time;
		TMU_Buffer[ACTIVE_TASKS].periodic = periodic;
		TMU_Buffer[ACTIVE_TASKS].fun_ptr = fun_ptr;
		ACTIVE_TASKS++;

	}

	return retvalue;

}

/*Dispatcher function that handle if that is the time to call the function or not */
EnmTMUError TMU_Dispatch() {
	uint8 retvalue = OK;
	uint8 index;
	if (ISR_Flag == 1) /*there is isr change */
	{
		for (index = 0; index < ACTIVE_TASKS; index++) {

			if (flags[index] >= TMU_Buffer[index].delay_time)/*time to call the function */
			{
				flags[index] = 0;
				if (TMU_Buffer[index].periodic == One_shot) /*on shot */
				{
					(*TMU_Buffer[index].fun_ptr)();
					TMU_Stop_Timer(TMU_Buffer[index].fun_ptr);
					index--;
				} else {

					(*TMU_Buffer[index].fun_ptr)();
				}
			}

		}
		ISR_Flag = 0;
	}

	return retvalue;
}

/*TMU stop function takes the name of the task to stop */
EnmTMUError TMU_Stop_Timer(void (*fun_ptr)(void)) {
	uint8 retvalue = OK;
	uint8 index;

	for (index = 0; index < ACTIVE_TASKS; index++) {
		if (TMU_Buffer[index].fun_ptr == fun_ptr) {
			TMU_Buffer[index] = TMU_Buffer[ACTIVE_TASKS - 1];/*overwrite the stop task with the last task in the buffer */
			flags[index] = flags[ACTIVE_TASKS - 1];/*overwrite the stop flag with the last flag*/

			ACTIVE_TASKS--;
			break;
		} else {
			retvalue = NOK;
		}

	}

	return retvalue;

}

/*call back function to increment the flags  */
void flags_func() {
	uint16 index;
	ISR_Flag = 1;
	static uint16 res = 0;/*static variable increment every time isr call  */
	res++;
	if (res == global_resolution)/*resolution time */
	{
		res = 0;

		for (index = 0; index < ACTIVE_TASKS; index++) {
			flags[index]++;/*increment flags */
		}

	}
}

