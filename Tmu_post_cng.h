/*
 * Tmu_post_cng.h
 *
 *  Created on: 12 Oct 2019
 *      Author: RGB
 */

#ifndef TMU_POST_CNG_H_
#define TMU_POST_CNG_H_
#include "stdtypes.h"

#define MAX_NUM_TASKS 10

typedef  struct {

	uint8 Timer_id;
	uint8 Resolution ;
}TMU_ConfigType;


extern TMU_ConfigType Tmu_init_struct ;

#endif /* TMU_POST_CNG_H_ */
