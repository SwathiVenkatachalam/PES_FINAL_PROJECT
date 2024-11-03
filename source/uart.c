/*
 * @file        uart.c
 * @brief       Contains UART initialization and Interrupt handler function implementations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references   https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 *               Assignment 6
 */

#include <stdio.h>
#include "uart.h"

Q_T TxQ, RxQ; //Transmit and receive queues

/*
 * @name   uart_init
 * @brief  Function initializes UART0
 *
 * Function initializes UART0
 *
 * @param  uint32_t baud_rate
 * @return none
 */
//configure UART0 to communicate with the OpenSDA debug	MCU
void uart_init(uint32_t baud_rate)
{
	uint16_t sbr;

	//Clock gating enabled for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Disables UART	receiver and transmitter to allow access to control registers. 
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	//UART clock set to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	//Pins set to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	//Baud rate and oversampling ratio set
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>SHIFT_BY_EIGHT);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	//Interrupts for RX active edge and LIN break detect set, one stop bit selected
	UART0->BDH |= UART0_BDH_RXEDGIE(0) |
		      UART0_BDH_SBNS(STOP_BITS) |
		      UART0_BDH_LBKDIE(0);

	//Don't enable loopback mode, use data bit mode, parity
	UART0->C1 = UART0_C1_LOOPS(0)     |
		    UART0_C1_M(DATA_SIZE) |
		    UART0_C1_PE(PARITY)   |
		    UART0_C1_PT(EVEN);
	//Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) |
		    UART0_C3_ORIE(0)  |
		    UART0_C3_NEIE(0)  |
		    UART0_C3_FEIE(0)  |
		    UART0_C3_PEIE(0);

	//Clear error flags
	UART0->S1 = UART0_S1_OR(1) |
		    UART0_S1_NF(1) |
		    UART0_S1_FE(1) |
		    UART0_S1_PF(1);

	//Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	//Set NVIC priorities
	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	//Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);

	//Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	//Clear the UART RDRF flag
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

	//Initialize cbfifo transmit and receive queues
	cbfifo_create(&RxQ);
	cbfifo_create(&TxQ);
}

/*
 * @name   UART0_IRQHandler
 * @brief  UART0 interrupt handler
 *
 * UART0 interrupt handler
 *
 * @param  None
 * @return none
 */
void UART0_IRQHandler(void)
{
	uint8_t ch; //Variable to store or transmit the data

	//If interrupt due to error flags
	if (UART0->S1 & (UART_S1_OR_MASK |
			 UART_S1_NF_MASK |
			 UART_S1_FE_MASK |
			 UART_S1_PF_MASK))
	{
		// clear the error flags
		UART0->S1 |= UART0_S1_OR_MASK |
			     UART0_S1_NF_MASK |
			     UART0_S1_FE_MASK |
			     UART0_S1_PF_MASK;
		// read the data register to clear RDRF
		ch = UART0->D;
	}

	//If interrupt due to receiving a character; receive data register full (RDRF) flag is set
	if (UART0->S1 & UART0_S1_RDRF_MASK)
	{
		ch = UART0->D; //received a character from the D register
		UART0->D = ch; // The character is immediately sent back (echoed) by writing it back to the D register.

		//Enqueue a byte successfully in read buffer and check if it enqueued
		if(cbfifo_enqueue(&ch, 1, &RxQ) == 1)
		{
			;
		}
		else
		{
			// error - queue full- discard character
		}
	}

	//If interrupt due to transmitting a character
	if ((UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
	    (UART0->S1 & UART0_S1_TDRE_MASK))  // if the transmit data register empty (TDRE) flag is set.
	{
		// If transmit buffer not empty
		if (!cbfifo_empty(&TxQ))
		{
			cbfifo_dequeue(&ch, 1, &TxQ); //Dequeue the transmit buffer
			UART0->D=ch; //Transmit dequeued byte serially
		}
		else
		{
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}

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
int __sys_write(int handle, char *buf, int size) //function enables sending data over UART, managing the transmit buffer.
{
	if(size <= 0 || buf == NULL) //checks if the size is valid and if the buffer is not null; i/p validation
		return ERROR;

	// It waits until there is enough space in the transmit buffer.
	while(size > (Q_MAX_SIZE - cbfifo_length(&TxQ))); // wait for space to open up

	//The data from the buffer is enqueued into the transmit queue. If it fails, it returns an error.
	if(cbfifo_enqueue(buf, size, &TxQ) != size)
		return ERROR;

	//start transmitter if it isn't already running
	//If the transmitter interrupt is not enabled, it sets it to start transmission.
	if (!(UART0->C2 & UART0_C2_TIE_MASK))
	{
		UART0->C2 |= UART0_C2_TIE(1);
	}

	return 0; //Return on success
}

/*
 * @name   __sys_readc
 * @brief  Function called by getchar
 *
 * Redirects characters from serial terminal to UART0
 *
 * @param  None
 * @return int 0 on success and -1 on failure
 */
int __sys_readc(void) //function reads characters from the UART receive buffer, waiting for data as necessary.
{
	char ch;
	while((cbfifo_length(&RxQ)) == 0); //Wait till the receive buffer is not empty; It waits until there is data in the receive queue

	if(cbfifo_dequeue(&ch, 1, &RxQ) == 1) //Dequeue the byte
		return ch; //Return byte
	else
		return ERROR; //Dequeue operation failed
}
