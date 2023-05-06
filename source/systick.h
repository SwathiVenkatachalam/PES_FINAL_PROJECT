/*
 * @file        systick.h
 * @brief       Function prototypes of systick timer delays
 *
 * Contains Function prototypes of systick timer delays
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE, gcc
 * @references  Assignment 3 question file
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include<stdint.h>

typedef uint32_t ticktime_t; //Time since boot, in sixteenth of a second

/*
 * @name   init_systicktimer
 * @brief  initializing SysTick Timer
 *
 * initializing SysTick Timer
 *
 * @param  void
 * @return void
 */
void init_systicktimer();


/*
 * @name   systick_handler
 * @brief  Handles systick timer, interrupt generated for every specific period
 *
 * Handles systick timer
 *
 * @param  void
 * @return void
 */
void SysTick_Handler();


/*
 * @name   time_now
 * @brief  time since startup, in sixteenth of a second
 *
 * time since startup, in sixteenth of a second
 *
 * @param  void
 * @return uint32_t real_time
 */
ticktime_t now();


/*
 * @name   reset_timer
 * @brief  Resets timer to 0
 *
 * Resets timer to 0
 *
 * @param  void
 * @return void
 */
void reset_timer();

/*
 * @name   get_timer
 * @brief  Ticks since the last call to reset_timer()
 *
 * Returns ticks since the last call to reset_timer()
 *
 * @param  void
 * @return ticktime_t
 */
ticktime_t get_timer();


#endif /* SYSTICK_H_ */
