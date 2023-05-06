/*
 * @file        commandprocessor.c
 * @brief       Function Implementation of commands and extra credit commands
 *
 * Function Implementation of author, sp, dump, info and help commands
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE, gcc
 * @references  Assignment 6
 */
#include "commandprocessor.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "MKL25Z4.h"
#include <math.h>
#include "accelerometer.h"

#include "led.h"
#include "musical_tones.h"
#include "test_queue.h"
#include "test_sine.h"

int commandprocessor_stop = 0;

/*
 * @name   author
 * @brief  Prints author name
 *
 *Function handles command "author", prints author name
 *
 * @param  void
 * @return void
 */
void author()
{
	printf("\r\nSwathi Venkatachalam\r\n"); //Prints author name
}

/*
 * @name   cbfifo_test
 * @brief  Runs queue tests
 *
 * Runs queue tests
 *
 * @param  void
 * @return void
 */
void cbfifo_test()
{
	int success = test_cbfifo();
	if (success == 1)
		printf("\n\rPass: All cbfifo test cases have passed!\n\r");
	else
		printf("\n\rFail: All cbfifo test cases have not passed!\n\r");
}

/*
 * @name   systick_test
 * @brief  Runs systick test
 *
 * Runs systick test
 *
 * @param  void
 * @return void
 */
void systick_test()
{
	//testing if 1 second has passed
	printf("\r\nTesting if systick timer crosses 1 second");
	reset_timer();
	while(get_timer()<16); //Wait for 1 second to elapse
	if (get_timer()*63.5>=1000) //Check if time is greater or equal to 1 sec
		printf("\n\rPass: Systick Timer test has passed!\n\r");
	else
		printf("\n\rFail: Systick Timer test has passed!\n\r");
}

/*
 * @name   sinewave_test
 * @brief  Runs sinewave tests
 *
 * Runs sinewave tests
 *
 * @param  void
 * @return void
 */
void sinewave_test()
{
	int success = test_sin();
	if (success == 1)
		printf("\n\rPass: Sine wave accuracy test passed!\n\r");
	else
		printf("\n\rFail: Sine wave accuracy test failed!\n\r");

}
/*
 * @name   display
 * @brief  Prints roll angle
 *
 *Prints roll angle
 *
 * @param  none
 * @return none
 */
void display()
{
	read_full_xyz();
	int roll = (int)convert_xyz_to_roll();
	if (roll < 0)
	{
		roll = -roll;
	}
	printf("\r\nThe roll angle in degrees is: %d\n\r", roll);
	if (fabs(roll) >= 0 && fabs(roll) <= 5)
	{
		Control_RGB_LEDs(0, 1, 0);
	}
	else if (fabs(roll) > 5 && fabs(roll) <= 45)
	{
		Control_RGB_LEDs(1, 1, 1);
	}
	else if (fabs(roll) > 45 && fabs(roll) <= 90)
	{
		Control_RGB_LEDs(1, 1, 0);
	}
	else if (fabs(roll) > 90 && fabs(roll) <= 135)
	{
		Control_RGB_LEDs(1, 0, 1);
	}
	else if (fabs(roll) > 135 && fabs(roll) <= 179)
	{
		Control_RGB_LEDs(0, 1, 1);
    }
}

/*
 * @name   terminate
 * @brief  Terminates command processor
 *
 * Terminates command processor
 *
 * @param  none
 * @return none
 */
void terminate()
{
	commandprocessor_stop = 1;
	printf("\n\rCommand Processor terminated!!\n\r");
	printf("\n\rTunes will play based on accelerometer roll angle.\n\r");
	printf("\n\rTo initiate command processor press reset!\n\r");
}

/*
 * @name   help
 * @brief  Prints a help message with info about all of the supported commands.
 *
 *Prints a help message with info about all of the supported commands.
 *
 * @param  none
 * @return none
 */
void help()
{
	printf("\r\n---------------------------------------------------------------------\r");
	printf("\r\nMusical Tones Player Based on Acceleration Angle Command Processor   \r");
	printf("\r\n---------------------------------------------------------------------\r");
	printf("\r\nAUTHOR       Prints author name.                                     \r");
	printf("\r\nDISPLAY      Prints current roll angle                               \r");
	printf("\r\nCBFIFO_TEST  Runs cbfifo tests                                       \r");
	printf("\r\nSYSTICK_TEST Runs systick timer test                                 \r");
	printf("\r\nTERMINATE    Terminates command processor                            \r");
	printf("\r\nHELP     Prints information about all of the supported commands.     \r");
	printf("\r\n                                                                     \r");
	printf("\r\nCommands are case-insensitive...                                     \r");
	printf("\r\nEnter any command to proceed...                                      \r");
	printf("\r\n---------------------------------------------------------------------\r\n");
}
