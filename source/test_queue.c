/*
 * @file        test_queue.c
 * @brief       Function Implementation of FIFO (First In First Out) Queue
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE, gcc
 * @references  https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/queue.c
 *              Assignment 6 https://github.com/shashankchandrasekaran/PES_Assignment_6/blob/main/source/test_cbfifo.c
 *              Assignment 2
 */

#include "queue.h"
#include "test_queue.h"

#include <stdio.h>
#include <string.h>

int test_cbfifo()
{
	Q_T RX; //Declare a buffer
	//Testing CBFIFO
	cbfifo_create(&RX);
	int success = 0;

	//1 Enqueuing nbytes first time that is less than capacity of array
	size_t expenqbytes = 22;
	char values[] = "WeGotThisJustKeepGoing";
	size_t calenqbytes = cbfifo_enqueue(&values[0], strlen(values), &RX);
	if(calenqbytes == expenqbytes)
		success++;

	//2 Enqueuing a null element
	size_t enqbytes = cbfifo_enqueue(NULL, 3, &RX);
	if (enqbytes == -1)
		success++;

	//3 Dequeuing the dequeued value in a null pointer
	size_t deqbytes = cbfifo_dequeue(NULL, 100, &RX);
	if (deqbytes == 0)
		success++;

	//4 Dequeuing more than the available space in buffer
	char deqdata[22];
	int expdeqbytes = 22;
	deqbytes = cbfifo_dequeue(deqdata, 30, &RX);
	if (deqbytes == expdeqbytes)
		success++;

	//5 Enqueuing more than the capacity of buffer
	expenqbytes = 256;
	char value0[]="C is a procedural programming language. It was initially developed by Dennis Ritchie as a system programming language to write an operating system. The main features of C language include low-level access to memory, simple set of keywords, and a clean style, these features make C language suitable for system programming like operating system or compiler development."
				  "C is a procedural programming language. It was initially developed by Dennis Ritchie as a system programming language to write an operating system. The main features of C language include low-level access to memory, simple set of keywords, and a clean style, these features make C language suitable for system programming like operating system or compiler development.";
	enqbytes = cbfifo_enqueue(value0, strlen(value0)+3, &RX);
	if(enqbytes == expenqbytes)
		success++;
	printf("Success = %d\n\r", success);
	//6 Combination of enqueuing and dequeuing
	expenqbytes = 20;
	expdeqbytes = 20;
	char value[] = "IamdoingPESassignment6testcases";
	deqbytes = cbfifo_dequeue(deqdata, 20, &RX);
	enqbytes = cbfifo_enqueue(value, 30, &RX);
	if ((deqbytes == expdeqbytes) && (enqbytes == expenqbytes))
		success++;

	//7 When nbytes=0 is passed in enqueue and dequeue function
	if ((cbfifo_enqueue(values, 0, &RX) == 0) && (cbfifo_dequeue(deqdata, 0, &RX) == 0))
		success++;

	//8 Checking if length is correctly returned after performing dequeue operation
	size_t callength,explength = 156;
	char deqdata1[100];
	cbfifo_dequeue(deqdata1, 100, &RX);
	callength = cbfifo_length(&RX);
	if(callength == explength)
		success++;

	//9 Passing integer as input
	expenqbytes = 4;
	int x = 310;
	enqbytes = cbfifo_enqueue(&x, 4, &RX);
	if(enqbytes == expenqbytes)
		success++;

	if(success == 9)
		return 1;
	else
		return 0;
}
