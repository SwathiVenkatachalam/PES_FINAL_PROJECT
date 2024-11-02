/*
 * @file        led.c
 * @brief       Initialization of LED function declarations
 *
 * Initialization of LED function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @reference   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/LEDs.c
 *
 */

#include "led.h"
// CMSIS: Cortex Microcontroller Software Interface Standard: Hardware abstraction layer, put out by ARM
// Many MCU vendors create Cortex-M-based MCUs
// to use CMSIS basics:  #include <device.h>
//Using	CMSIS to Access	Hardware Registers with	C Code
#include <MKL25Z4.H> //File can be opened in MCUXpresso IDE

/*
 * @name   init_RGB_LEDs
 * @brief  Initializes RGB
 *
 * Initializes RGB, GPIOs for LEDs
 *
 * @param  none
 * @return void
 */
void init_RGB_LEDs()
{
	// Enable clock to ports B and D
	// Ref Manual: Set bit 10 and 12 for Port B and Port D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	// Make 3 pins GPIO
	// Access particlar pins PCR register, clear bit and set bit 8
	PORTB->PCR[RED_LED_POS]   &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS]   |= PORT_PCR_MUX(1);
	
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);
	
	PORTD->PCR[BLUE_LED_POS]  &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS]  |= PORT_PCR_MUX(1);

	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
}

/*
 * @name   Control_RGB_LEDs
 * @brief  sets RGB
 *
 * Turns RGB LEDs on and off
 *
 * @param  unsigned int red_on, unsigned int green_on, unsigned int blue_on
 * @return void
 */
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on)
{
	// Look at FRDMKL25Z usermanual pg13 schematics, state is inverted. pin should be 0 for LED to glow. And 1 for LED off.
	//Write value
	if (red_on) //LED ON
		PTB->PCOR = MASK(RED_LED_POS); //Port Clear Output Register
	else //LED OFF
		PTB->PSOR = MASK(RED_LED_POS); //Port Set Output Register

	if (green_on)
		PTB->PCOR = MASK(GREEN_LED_POS);
	else
		PTB->PSOR = MASK(GREEN_LED_POS);

	if (blue_on)
		PTD->PCOR = MASK(BLUE_LED_POS);
	else
		PTD->PSOR = MASK(BLUE_LED_POS);
}
