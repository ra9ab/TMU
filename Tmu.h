/*
 * Tmu.h
 *
 *  Created on: 12 Oct 2019
 *      Author: RGB
 */

#ifndef TMU_H_
#define TMU_H_
#include "Tmu_post_cng.h"
#include "timer.h"

typedef enum  {OkK,NOKK}EnmTMUError;
#define Periodic 1
#define One_shot 2

/*--------------------------------------------*/

typedef struct {
	uint16 delay_time ;
	void (*fun_ptr)(void);
	uint8 periodic ;
	uint8 state ;
}TMU_start;



extern TMU_start TMU_Buffer[MAX_NUM_TASKS] ;




/*--------------------------------------------*/

EnmTMUError TMU_Init (const TMU_ConfigType * ConfigPtr ) ;
EnmTMUError TMU_Start_Timer (uint16 delay_time , uint8 periodic , void (*fun_ptr)(void));
EnmTMUError TMU_Stop_Timer ( void (*fun_ptr)(void));
EnmTMUError TMU_Dispatch (void);
void flags_func(void);





#endif /* TMU_H_ */
