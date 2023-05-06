/*
 * @file        systick.c
 * @brief       Function Implementation of systick timer delays
 *
 * Contains Function Implementation of systick timer delays
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE, gcc
 */

#include <musical_tones.h>
#include "systick.h"

#include <stdio.h>
#include "MKL25Z4.h"


#define SYSTICK_PRIORITY (3)
#define SYSTICK_LOAD     (187500) //Load value for obtaining 62.5 msec delay
#define MS_DELAY_        (62.5)

ticktime_t ms_delay = 0;
ticktime_t timer = 0; //Variables used for timing calculations

/*
 * @name   init_systicktimer
 * @brief  initializing SysTick Timer
 *
 * initializing systick timer
 *
 * @param  void
 * @return void
 */
void init_systicktimer()
{
	SysTick->LOAD = SYSTICK_LOAD; //Set reload register
	NVIC_SetPriority(SysTick_IRQn, SYSTICK_PRIORITY); //Set Priority for SysTick Interrupt
	SysTick->VAL = ZERO;                   //Load the SysTick Counter Value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | //Enable Interrupt, alt. clock source
			        SysTick_CTRL_ENABLE_Msk; //Enable SysTick timer
}

/*
 * @name   systick_handler
 * @brief  Handles systick timer, interrupt generated for every specific period
 *
 * Handles systick timer
 *
 * @param  void
 * @return void
 */

void SysTick_Handler()
{
	ms_delay++;
}

/*
 * @name   time_now
 * @brief  time since startup, in sixteenth of a second
 *
 * time since startup, in sixteenth of a second
 *
 * @param  void
 * @return uint32_t real_time
 */

ticktime_t now()
{
	return ms_delay * MS_DELAY_;
}

/*
 * @name   reset_timer
 * @brief  Resets timer
 *
 * Resets timer to
 *
 * @param  void
 * @return void
 */

void reset_timer()
{
	timer = ms_delay;
}

/*
 * @name   get_timer
 * @brief  Ticks since the last call to reset_timer()
 *
 * Returns ticks since the last call to reset_timer()
 *
 * @param  void
 * @return ticktime_t ( Start variable count since last call to reset)
 *
 */

ticktime_t get_timer()
{
	return (ms_delay - timer);
}
