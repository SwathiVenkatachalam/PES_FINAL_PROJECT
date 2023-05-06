/*
 * @file        led.h
 * @brief       Initialization of LED function declarations
 *
 * Initialization of LED function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @reference   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/inc/LEDs.h
 *
 */

#ifndef LED_H_
#define LED_H_

// Freedom KL25Z LEDs
#define RED_LED_POS   (18)    // on port B
#define GREEN_LED_POS (19)	  // on port B
#define BLUE_LED_POS  (1)     // on port D
#define MASK(x)       (1UL << (x))

/*
 * @name   init_RGB_LEDs
 * @brief  Initializes RGB
 *
 * Initializes RGB
 *
 * @param  none
 * @return void
 */
void init_RGB_LEDs();

/*
 * @name   Control_RGB_LEDs
 * @brief  sets RGB
 *
 * sets RGB
 *
 * @param  unsigned int red_on, unsigned int green_on, unsigned int blue_on
 * @return void
 */
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);

#endif /* LED_H_ */
