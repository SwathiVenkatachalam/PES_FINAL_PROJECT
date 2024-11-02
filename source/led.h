/*
 * @file        led.h
 * @brief       Initialization of LED function declarations
 *
 * Initialization of LED function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @reference   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/inc/LEDs.h
 *              FRDMKL25Z User manual
 *
 */
// directives are used in header files to prevent multiple inclusions of same header file in single compilation unit, a technique called include guard.
// prevents redefinition errors 
#ifndef LED_H_ // Checks if LED_H_ has not been defined; #ifndef LED_H_ will evaluate to false, code within the guard will be skipped.
// Defines LED_H_ to prevent future inclusions of this file
#define LED_H_ 


// Freedom KL25Z LEDs from FRDM-KL25Z User's Manual Pg 12-13 (schematics and Connections Table)
#define RED_LED_POS   (18)    // on port B
#define GREEN_LED_POS (19)	  // on port B
#define BLUE_LED_POS  (1)     // on port D
// creates bit mask, that bit set to 1, all others 0
#define MASK(x)       (1UL << (x))

/*
 * @name   init_RGB_LEDs
 * @brief  Initializes RGB
 *
 * Initializes RGB, GPIOs for LEDs
 *
 * @param  none
 * @return void
 */
void init_RGB_LEDs();

/*
 * @name   Control_RGB_LEDs
 * @brief  sets RGB
 *
 * Turns RGB LEDs on and off
 *
 * @param  unsigned int red_on, unsigned int green_on, unsigned int blue_on
 * @return void
 */
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);

#endif /* LED_H_ */
// Ends the include guard
