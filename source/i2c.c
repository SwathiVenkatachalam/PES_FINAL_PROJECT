/*
 * @file        i2c.c
 * @brief       Initialization of I2C functions for MMA accelerometer
 *
 * Initialization of LED function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @reference   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/i2c.c
 *
 */

#include <MKL25Z4.H>
#include "i2c.h"

#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN		I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC			I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 		i2c_wait();

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK             I2C0->C1 &= ~I2C_C1_TXAK_MASK


int lock_detect=0;
int i2c_lock=0;

/*
 * @name   init_i2c0
 * @brief  Initializes I2C0
 *
 * Initializes RGB
 *
 * @param  none
 * @return void
 */
void init_i2c()
{
	//clock i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);

	//set pins to I2C function
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	PORTE->PCR[25] |= PORT_PCR_MUX(5);

 	I2C0->F = (I2C_F_ICR(0x10) | I2C_F_MULT(0));

	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);
}


void i2c_busy()
{
	// Start Signal
	lock_detect=0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	I2C0->C1 |=  I2C_C1_IICEN_MASK;
	// Write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK; //set MASTER mode
	I2C0->C1 |= I2C_C1_TX_MASK; //Set transmit (TX) mode
	I2C0->D = 0xFF;
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U) {
	} //wait interrupt
	I2C0->S |= I2C_S_IICIF_MASK; //clear interrupt bit

	//Clear arbitration error flag
	I2C0->S |= I2C_S_ARBL_MASK;

	//Send start
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_TX_MASK; //Set transmit (TX) mode
	I2C0->C1 |= I2C_C1_MST_MASK; //START signal generated

	I2C0->C1 |= I2C_C1_IICEN_MASK;
	//Wait until start is send

	//Send stop
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK; //set SLAVE mode
	I2C0->C1 &= ~I2C_C1_TX_MASK; //Set Rx
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	// wait
	//Clear arbitration error & interrupt flag
	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;
	lock_detect=0;
	i2c_lock=1;
}

void i2c_wait()
{
	lock_detect = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK)==0) & (lock_detect < 200))
	{
		lock_detect++;
	}
	if (lock_detect >= 200)
		i2c_busy();
	I2C0->S |= I2C_S_IICIF_MASK;
}

/*
 * @name   i2c_start
 * @brief  Send start sequence
 *
 * Send start sequence
 *
 * @param  none
 * @return void
 */
void i2c_start()
{
	I2C_TRAN;	 //set to transmit mode
	I2C_M_START; //send start
}

/*
 * @name   i2c_read_setup
 * @brief  Send device and register address
 *
 * Send device and register address
 *
 * @param  uint8_t dev, uint8_t address
 * @return void
 */
void i2c_read_setup(uint8_t dev, uint8_t address)
{
	I2C0->D = dev;	    //send dev address
	I2C_WAIT		    //wait for completion

	I2C0->D =  address;	//send read address
	I2C_WAIT			//wait for completion

	I2C_M_RSTART;	    //repeated start
	I2C0->D = (dev|0x1);//send dev address (read)
	I2C_WAIT            //wait for completion

	I2C_REC;		    //set to receive mode
}

/*
 * @name   i2c_repeated_read
 * @brief  Read a byte and ack/ nack as appropriate
 *
 * Initializes RGB
 *
 * @param  uint8_t isLastRead
 * @return void
 */
uint8_t i2c_repeated_read(uint8_t isLastRead)
{
	uint8_t data;

	lock_detect = 0;

	if(isLastRead)
	{
		NACK;	         //set NACK after read
	}
	else
	{
		ACK;	        //ACK after read
	}

	data = I2C0->D;	    //dummy read
	I2C_WAIT		    //wait for completion

	if(isLastRead)
	{
		I2C_M_STOP;		//send stop
	}
	data = I2C0->D;		//read data

	return  data;
}

/*
 * @name   i2c_read_byte
 * @brief  Reads a byte data to dev address
 *
 * Reads a byte data to dev address using 7 but addressing
 *
 * @param  uint8_t dev, uint8_t address
 * @return void
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C_TRAN;				//set to transmit mode
	I2C_M_START;			//send start
	I2C0->D = dev;			//send dev address
	I2C_WAIT				//wait for completion

	I2C0->D =  address;		//send read address
	I2C_WAIT				//wait for completion

	I2C_M_RSTART;			//repeated start
	I2C0->D = (dev|0x1);	//send dev address (read)
	I2C_WAIT				//wait for completion

	I2C_REC;				//set to recieve mode
	NACK;					//set NACK after read

	data = I2C0->D;			//dummy read
	I2C_WAIT				//wait for completio

	I2C_M_STOP;				//send stop
	data = I2C0->D;			//read data

	return data;
}

/*
 * @name   i2c_write_byte
 * @brief  Writes a byte data to dev address
 *
 * Writes a byte data to dev address using 7 but addressing
 *
 * @param  uint8_t dev, uint8_t address, uint8_t data
 * @return void
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{

	I2C_TRAN;			//set to transmit mode
	I2C_M_START;		//send start
	I2C0->D = dev;		//send dev address
	I2C_WAIT			//wait for ack

	I2C0->D =  address;	//send write address
	I2C_WAIT

	I2C0->D = data;		//send data
	I2C_WAIT
	I2C_M_STOP;
}
