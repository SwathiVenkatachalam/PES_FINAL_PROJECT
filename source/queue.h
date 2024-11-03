/*
 * @file        queue.h
 * @brief       Function Declaration of FIFO (First In First Out) Queue
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE, gcc
 * @references  Alexander Dean
 *              https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/inc/queue.h
 *              Assignment 6
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>

#define Q_MAX_SIZE (256) //Assuming maximum number of nodes don't exceed 256 in fifo


//Structure defined for transmit and receive buffer, need 2 buffers
typedef struct{
	int front;
	int rear;
	int length; //no of elements in use
	char qdata[Q_MAX_SIZE];
}Q_T;

/*
 * @name   cbfifo_create
 * @brief  Creates queue
 *
 * Creates queue, init FIFO
 *
 * @param  Q_T * q : The buffer which needs to be enqueued (TxQ or RxQ)
 * @return none
 */
void cbfifo_create(Q_T * q);

/*
 * @name   cbfifo_empty
 * @brief  Checks if queue is empty
 *
 * Checks if queue is empty
 *
 * @param  Q_T * q
 * @return int: 1 if the FIFO is empty and 0 if it is not
 */
int cbfifo_empty(Q_T * q);

/*
 * @name   cbfifo_length
 * @brief  Returns the number of bytes currently on the FIFO.
 *
 * Returns the number of bytes currently on the FIFO
 *
 * @param  Q_T * q
 * @return Number of bytes currently available to be dequeued from the FIFO
 */
int cbfifo_length(Q_T *q);

/*
 * @name   cbfifo_enqueue
 * @brief  Enqueues data onto the FIFO
 *
 * Enqueues data onto the FIFO
 *
 * @param  void *buf, int nbyte, Q_T *q
 *         buf    Pointer to the data
 *         nbyte  Max number of bytes to enqueue
 *	       *q     Queue which needs to be enqueued (TxQ or RxQ)
 * @return int    number of bytes actually enqueued
 */
int cbfifo_enqueue(void *buf, int nbyte, Q_T *q);

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
int cbfifo_dequeue(void *buf, int nbyte, Q_T *q);


#endif /* QUEUE_H_ */
