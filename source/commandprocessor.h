/*
 * @file        commandprocessor.h
 * @brief       Function Declaration of commands and extra credit commands
 *
 * Function Declaration of author, sp, dump, info and help commands
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE, gcc
 * @references  Assignment 6
 */

#ifndef COMMANDPROCESSOR_H_
#define COMMANDPROCESSOR_H_

extern int commandprocessor_stop;

//Function Pointer to Invoke Commands by the input from the user
typedef void (*command_handler_t)(int, char *argv[]);

//Structure to store the parameters of the commands
typedef struct {
	const char *name;
	command_handler_t handler;
	const char *help_string;
} command_table_t;

/*
 * @name   author
 * @brief  Prints author name
 *
 *Function handles command "author", prints author name
 *
 * @param  void
 * @return void
 */
void author();

/*
 * @name   cbfifo_test
 * @brief  Runs queue tests
 *
 * Runs queue tests
 *
 * @param  void
 * @return void
 */
void cbfifo_test();

/*
 * @name   systick_test
 * @brief  Runs systick test
 *
 * Runs systick test
 *
 * @param  void
 * @return void
 */
void systick_test();

/*
 * @name   sinewave_test
 * @brief  Runs sinewave tests
 *
 * Runs sinewave tests
 *
 * @param  void
 * @return void
 */
void sinewave_test();

/*
 * @name   display
 * @brief  Prints current roll angle
 *
 *Function handles command "display", prints roll angle
 *
 * @param  void
 * @return void
 */
void display();

/*
 * @name   help
 * @brief  Prints a help message with info about all of the supported commands.
 *
 * Prints a help message with info about all of the supported commands.
 *
 * @param  none
 * @return none
 */
void help();

/*
 * @name   terminate
 * @brief  Terminates command processor
 *
 * Terminates command processor
 *
 * @param  none
 * @return none
 */
void terminate();

//Array of structures
//Object of the command_table_t
static const command_table_t commands[] = {
		{"Author", author, "author - Prints string with name"},
		{"Cbfifo_test", cbfifo_test, "cbfifo_test - Runs cbfifo tests"},
		{"Systick_test", systick_test, "systick_test - Runs systick timer test"},
		{"Sinewave_test", sinewave_test, "sinewave_test - Tests the sine wave generated"},
		{"Display", display, "display - Prints current roll angle"},
		{"Terminate", terminate, "terminate - Terminates command processor and gets fully into action"},
		{"Help", help, "help - Print this help message"}
};

//Number of commands
static const int num_commands = sizeof(commands) / sizeof(command_table_t);

#endif /* COMMANDPROCESSOR_H_ */
