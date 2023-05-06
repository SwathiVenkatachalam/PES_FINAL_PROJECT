/*
 * @file        uart.h
 * @brief       Contains UART initialization and Interrupt handler function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references  Alexander Dean
 *              https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 *              Assignment 6
 */

#ifndef UART_H_
#define UART_H_

#include <MKL25Z4.H>
#include <stdint.h>
#include "queue.h"

#define BAUD_RATE            (38400) //Baud rate: 38400
#define DATA_SIZE            (1) // Data size 9 bits; parity bit takes 9th bit
#define PARITY               (1) //Parity Enable
#define EVEN                 (0) //Parity Even
#define STOP_BITS            (0)     //Stop bits: 1

#define USE_UART_INTERRUPTS  (0)     // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE (16)    // Over sample rate
#define BUS_CLOCK            (24e6)  // Bus clock frequency: 24MHz
#define SYS_CLOCK            (24e6)  // System clock frequency: 24MHz

#define SHIFT_BY_EIGHT       (8)     // Shifting sbr by 8 bits
#define ERROR                (-1)    // Returns -1 on error

/*
 * @name   uart_init
 * @brief  Function initializes UART0
 *
 * Function initializes UART0
 *
 * @param  uint32_t baud_rate
 * @return none
 */
void uart_init(uint32_t baud_rate);

/*
 * @name   UART0_IRQHandler
 * @brief  UART0 interrupt handler
 *
 * UART0 interrupt handler
 *
 * @param  None
 * @return none
 */
void UART0_IRQHandler();

/*
 * @name   __sys_write
 * @brief  Function called by printf
 *
 * Redirects characters from UART0 to the serial terminal
 *
 * @param  int handle (Writes bytes to stdout (Handle=1) or stderr (Handle=2)),
 *         char *buf (string to be written),
 *         int size (bytes of data to be transmitted)
 * @return int 0 on success and -1 on failure
 */
int __sys_write(int handle, char *buf, int size);

/*
 * @name   __sys_readc
 * @brief  Function called by getchar
 *
 * Redirects characters from serial terminal to UART0
 *
 * @param  None
 * @return int 0 on success and -1 on failure
 */
int __sys_readc();

#endif /* UART_H_ */
