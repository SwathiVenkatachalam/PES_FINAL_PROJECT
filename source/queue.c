/*
 * @file        queue.c
 * @brief       Function Implementation of FIFO (First In First Out) Queue
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE, gcc
 * @references  https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/queue.c
 *              Assignment 6 https://github.com/ECEN5813/assignment-6-breakfastserial-SwathiVenkatachalam/blob/main/source/llfifo.c
 *              https://www.geeksforgeeks.org/queue-linked-list-implementation/
 */

#include <MKL25Z4.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "queue.h"


#define INITIAL_VALUE (-1) //Sets init val for front and rear indexes, indicating an empty state
#define ERROR         (-1) //Used as return val for error conditions in queue ops

/*
 * @name   cbfifo_create
 * @brief  Creates queue
 *
 * Creates queue
 *
 * @param  Q_T * q
 * @return none
 */
void cbfifo_create(Q_T * q)
{
	q->front = INITIAL_VALUE;
	q->rear  = INITIAL_VALUE;
	q->length= 0;
	memset(q->qdata,0,Q_MAX_SIZE);
}

/*
 * @name   cbfifo_empty
 * @brief  Checks if queue is empty
 *
 * Checks if queue is empty
 *
 * @param  Q_T * q
 * @return int: 1 if the FIFO is empty and 0 if it is not
 */
int cbfifo_empty(Q_T * q)
{
	return q->length == 0;
}

/*
 * @name   llfifo_length
 * @brief  Returns the number of bytes currently on the FIFO.
 *
 * Returns the number of bytes currently on the FIFO
 *
 * @param  Q_T * q
 * @return Number of bytes currently available to be dequeued from the FIFO
 */
int cbfifo_length(Q_T *q)
{
	return q->length;
}

/*
 * @name   cbfifo_enqueue
 * @brief  Enqueues data onto the FIFO
 *
 * Enqueues data onto the FIFO
 *
 * @param  void *buf, int nbyte, Q_T *q
 *         buf    Pointer to the data
 *         nbyte  Max number of bytes to enqueue
 *	     *q   Queue which needs to be enqueued (TxQ or RxQ)
 * @return int    number of bytes actually enqueued
 */
int cbfifo_enqueue(void *buf, int nbyte, Q_T *q)
{
	int store = 0, enqbytes = 0, temp = 0, i = 0;
	char *input = buf; //Character pointer created to point to buf

	uint32_t masking_state;
	masking_state = __get_PRIMASK(); 	// save current masking state
	__disable_irq();          	// disable interrupts
	
	if(input == NULL) //If the buffer is NULL, error condition
	{
		__set_PRIMASK(masking_state); //Enable the interrupts again before returning
		return ERROR;
	}
	else if((q->front==INITIAL_VALUE) && (q->rear==INITIAL_VALUE)) //If no bytes is inserted, insert the first byte of data
	{
		temp=INITIAL_VALUE; //variable used for enqueuing 1st byte in array
		q->front=q->rear=0; //rear and front now at 0th index of array
		q->qdata[0]=*input; //First byte enqueued in first element of array
		input++;
		q->length++;
	}
	if (q->length == Q_MAX_SIZE || nbyte == 0) //If the array is full or nbyte requested to front is zero
	{
		__set_PRIMASK(masking_state);
		return 0; //Indicate no bytes enqueued
	}
	else if(nbyte <= (Q_MAX_SIZE - q->length)) //If bytes to enqueue is less or equal to available space for new elements in array (max cap-used)
	{
		if(temp == INITIAL_VALUE) //To enqueue remaining bytes after 1st byte was inserted in array when write/front and read/rear was -1
		{
			for(i = 0; i < nbyte - 1; i++)
			{
				q->front=(q->front+1)&(Q_MAX_SIZE-1); //To update front in such a way that on last index of array, after incrementing goes to start address
				q->qdata[q->front] = *input; //1 byte inserted in array
				input++; //inc buffer ptr to next byte
				q->length++; //inc length
			}
			temp = 0; //Temp changed to zero as now the array has element
			__set_PRIMASK(masking_state);
			return nbyte; //Returns number of bytes enqueued
		}
		else //To enqueue nbytes when enqueue is not called first time and above if condition is met
		{
			for(i = 0; i < nbyte; i++)
			{
				q->front=(q->front+1)&(Q_MAX_SIZE-1);
				q->qdata[q->front] = *input;
				input++;
				q->length++;
			}
			__set_PRIMASK(masking_state);
			return nbyte;
		}
	}
	else if(nbyte > (Q_MAX_SIZE - q->length)) //When bytes to enqueue is more than the available space in array
	{
		if(temp == -1) //To enqueue remaining bytes after 1st byte was inserted in array when write and read was -1
		{
			store = Q_MAX_SIZE - q->length - 1; //available space
			for(i = 0;i < store; i++)
			{
				q->front = (q->front+1)&(Q_MAX_SIZE-1);
				q->qdata[q->front] = *input;
				input++;
				q->length++;
				enqbytes++;
			}
			temp = 0;
			__set_PRIMASK(masking_state);
			return enqbytes;
		}
		else  //To enqueue nbytes when enqueue is not called first time and above if condition is met
		{
			store = Q_MAX_SIZE - q->length;
			for(i = 0; i < store; i++)
			{
				q->front = (q->front+1)&(Q_MAX_SIZE-1);
				q->qdata[q->front] = *input;
				input++;
				q->length++;
				enqbytes++;
			}
			__set_PRIMASK(masking_state);
			return enqbytes;
		}
	}
	else
	{
		__set_PRIMASK(masking_state);
		return 0; //If no conditions above met, enqueue operation is not performed, return 0 bytes enqueued
	}
}

/*
 * @name   cbfifo_dequeue
 * @brief  Dequeue up to nbyte bytes of data from the FIFO
 *
 * Removed data will be copied into the buffer pointed to by buf
 *
 * @param  void *buf, int nbyte, Q_T *q
 *         buf    Destination for the dequeued data
 *         nbyte  Bytes of data requested
 *	       *q     Queue which needs to be dequeued (TxQ or RxQ)
 * @return int     number of bytes copied
 */
int cbfifo_dequeue(void *buf, int nbyte, Q_T *q)
{
	char *output = buf; //Character pointer created to point to buf

	uint32_t masking_state;
	masking_state = __get_PRIMASK(); 	// save current masking state
	__disable_irq(); 	// disable interrupts

	//Check if queue empty and input validation; buf where i/p val dequeued data would be copied is NULL; requested number of bytes to dequeue (nbyte) is zero
	if(((q->front == INITIAL_VALUE) && (q->rear == INITIAL_VALUE)) ||
	                                                q->length == 0 ||
		                                          buf == NULL  ||
		                                          nbyte == 0) //If the array is empty , return that 0 bytes were reard
	{
		__set_PRIMASK(masking_state);
		return 0; //0 bytes dequeued
	}

	else if (nbyte > q->length) //If byte to dequeue is more than length, dequeue all bytes available and return that
	{
		int deqbyte = q->length; //Since array contains length elements, all are dequeued
		for(int i = 0; i < deqbyte; i++)
		{
			*output = q->qdata[q->rear]; //dequeued data stored
			q->rear = (q->rear+1) & (Q_MAX_SIZE-1); //rear updated to next array index
			q->length--; //Length reduced
			output++; //buffer inc
		}
		__set_PRIMASK(masking_state);
		return deqbyte; //Return bytes dequeued
	}
	else if (nbyte <= q->length) //If byte to dequeue is less than or equal to length, dequeue those bytes
	{
		for(int i = 0; i < nbyte; i++)
		{
			*output = q->qdata[q->rear];
			q->rear = (q->rear+1) & (Q_MAX_SIZE-1);
			q->length--;
			output++;
		}
		__set_PRIMASK(masking_state);
		return nbyte; //Returns bytes dequeued
	}
	else
	{
	    __set_PRIMASK(masking_state);
	    return 0; //If no conditions above met, rear operation is not performed
	}
}
