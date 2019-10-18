/*
 * app.c
 *
 *  Created on: 13 Oct 2019
 *      Author: RGB
 */
#include "app.h"
void LED_1(void)
{
	toggle_bit(REG_PORTB,PIN4);
}
void LED_2(void)
{
	toggle_bit(REG_PORTB,PIN5);
}
void LED_3(void)
{
	toggle_bit(REG_PORTB,PIN6);

}


void LED_4(void)
{
	toggle_bit(REG_PORTB,PIN7);

	}
