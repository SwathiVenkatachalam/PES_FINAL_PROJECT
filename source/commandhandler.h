/*
 * @file        commandhandler.h
 * @brief       Function Declaration of command processor
 *
 * Contains accumulating string and lexical analysis function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE, gcc
 * @references  ECEN 5813 PES 21 Command Processing slides 26-28
 *              Assignment 6
 *
 */

#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_


/*
 * @name   accumulateString
 * @brief  Function handles string accumulation
 *
 *Function handles string accumulation
 *
 * @param  char *buf, int buf_size
 * @return void
 */
void accumulateString(char *buf, int buf_size);

/*
 * @name   lexicalAnalysis
 * @brief  Function for Lexical analysis and calling handlers
 *
 * Function for Lexical analysis and calling handlers
 *
 * @param  char *input
 * @return void
 */
void lexicalAnalysis(char *input);

/*
 * @name   commandprocessor
 * @brief  Accumulates string and performs lexical analysis
 *
 * Command processor main function that prompts user to enter command with "$$ " and executes the command
 *
 * @param  void
 * @return void
 */
void commandprocessor();

#endif /* COMMANDHANDLER_H_ */
