/*
 * @file        main.c
 * @brief       Application Entry Point
 *
 * Calls all functions
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @reference   Assignment 7 https://github.com/ECEN5813/assignment-7-waveforms-SwathiVenkatachalam/blob/main/source/main.c
 *              https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/main.c
 */

#include <stdio.h>
#include <math.h>

#include "sysclock.h"
#include "uart.h"
#include "commandhandler.h"
#include "commandprocessor.h"

#include "i2c.h"
#include "accelerometer.h"
#include "musical_tones.h"
#include "led.h"

//Main subroutine
int main()
{
	//Init board hardware.
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	//Init FSL debug console.
	BOARD_InitDebugConsole();
#endif
	int roll;
	test_sin();
	init_all();
	init_RGB_LEDs();
	init_i2c();
	if (!init_mma())
	{
		Control_RGB_LEDs(1, 0, 0);	//Light red error LED
		while (1)	//not able to initialize mma
			;
	}
	else
		Control_RGB_LEDs(0, 1, 0);

	sysclock_init();                 //initialize clock
	uart_init(BAUD_RATE);            //initialize uart0
	PRINTF("\n\rWelcome to the Command Processor of Musical Tones Player Based on Acceleration Angle!!\n\r");
	while(1)
	{
		commandprocessor();             //command processor begins
		read_full_xyz();                //read accelerometer
		roll = (int)convert_xyz_to_roll();
		play_tunes(roll);               //play tones
	}
	return ZERO;
}
