/*
 * app.c
 *
 *  Created on: 13 Oct 2019
 *      Author: RGB
 */
#include "app.h"
void LED_5(void)
{
	toggle_bit(REG_PORTB,PIN4);
	}
void LED_12(void)
{
	toggle_bit(REG_PORTB,PIN5);
}
void LED_8(void)
{
	toggle_bit(REG_PORTB,PIN6);

	}


