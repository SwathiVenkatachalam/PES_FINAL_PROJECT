/*
 * @file        commandhandler.c
 * @brief       Function Implementation of command processor
 *
 * Contains accumulating string and lexical analysis functions
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references  ECEN 5813 PES 21 Command Processing slides 26-28
 *              Assignment 6
 */

#include "commandhandler.h"
#include "commandprocessor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE     (256)
#define INITIAL_VALUE   (0)
#define ONE             (1)
#define EXECUTION_TIMES (2) 
#define CARRIAGE_RETURN ('\r')
#define BACKSPACE       ('\b')
#define NULL_CHAR       ('\0')
#define SPACE_CHAR      (' ')

#define ARGV_MAX_SIZE   (10)
#define SPACE           (32)

/*
 * @name   accumulateString
 * @brief  Function handles string accumulation
 *
 *Function handles string accumulation
 *
 * @param  char *buf, int buf_size
 * @return void
 */
void accumulateString(char *buf, int buf_size)
{
	memset(buf, INITIAL_VALUE, buf_size);   //Resetting variables before processing a new string
	int location = INITIAL_VALUE - ONE;

	while(buf[location] != CARRIAGE_RETURN) //Accumulate line
	{
		char character = getchar();         //Stores character received from user
		printf("%c", character);          //Echos character
		location++;
		buf[location] = character;          //Stores character for lexical analysis

		//dumb terminal; does what we ask as is. \b back space just goes back, no erasing, implement \b_\b
		if((buf[location] == BACKSPACE) && (location > INITIAL_VALUE)) //Handle backspace
		{
			int i = EXECUTION_TIMES;
			while(i != INITIAL_VALUE)
			{
				buf[location] = SPACE_CHAR; //Print space at current cursor
				location--;                 //Move cursor to previous location
				i--;
			}
			printf(" %c", BACKSPACE);
		}
	}
	buf[location] = NULL_CHAR;              //Terminate string with null character
}

/*
 * @name   lexicalAnalysis
 * @brief  Function for Lexical analysis and calling handlers
 *
 * Function for Lexical analysis and calling handlers
 *
 * @param  char *input
 * @return void
 */
void lexicalAnalysis(char *input)
{
	char *p = input;
	char *end;

	for (end = input; *end != NULL_CHAR; end++)
	{
		; // find end of string
	}

	char *argv[ARGV_MAX_SIZE]; //Array of character pointers to store address of arguments
	int argc = INITIAL_VALUE; //Variable to store number of arguments
	memset(argv, INITIAL_VALUE, sizeof(argv));

	char previous_val = *input; //Use this variable to store the previous value in input string

	for (p = input; p < end; p++) 	//Lexical Analysis: loading char, tokenization
	{
		if(*p > SPACE) //If the value is above space in ascii table
		{
			if(p == input || previous_val == SPACE || previous_val == NULL_CHAR) //If previous char is  first address/space/null
			{
				argv[argc] = p; //Store the start address of argument
				argc++;         //Increment number of argument
			}
		}
		else if(*p == SPACE) //Current value is space
		{
			if (previous_val != SPACE || previous_val != NULL_CHAR) //check previous value not space/null
			{
				*p = NULL_CHAR; //Force to null
			}
		}
		previous_val = *p; //Store previous byte in string
	}

	argv[argc] = NULL;

	if (argc == INITIAL_VALUE) // no command
		return;

	int valid_command = INITIAL_VALUE; //Used to check if a valid command is received or not
	for (int i = INITIAL_VALUE; i < num_commands; i++) //Execute commands/ error based on received command
	{
		if (strcasecmp(argv[0], commands[i].name) == INITIAL_VALUE) //Valid command check case wise
		{
			commands[i].handler(argc, argv); //Call command handler
			valid_command = 1; //Set valid command flag to true
			break;
		}
	}

	if(valid_command == INITIAL_VALUE) 	//Invalid command check using flag
	{
		printf("\n\rUnknown command: %s\n\r", input); // print unknown command
	}
}

/*
 * @name   commandprocessor
 * @brief  Accumulates string and performs lexical analysis
 *
 * Command processor main function that prompts user to enter command with "$$ " and executes the command
 *
 * @param  void
 * @return void
 */
void commandprocessor()
{
	char buf[BUFFER_SIZE]; //Used to store the string containing various arguments

	while (commandprocessor_stop != 1)
	{
		printf("$$ ");
		accumulateString(buf, BUFFER_SIZE); //Accumulate string
		lexicalAnalysis(buf);  //Pass the string for lexical analysis
	}
}
