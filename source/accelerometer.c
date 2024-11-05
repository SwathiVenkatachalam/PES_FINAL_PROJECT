/*
 * @file        accelerometer.c
 * @brief       Functions for MMA8451 accelerometer
 *
 * Functions for MMA8451 accelerometer
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references  https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/mma8451.c
 *
 */

#include <MKL25Z4.H>
#include "accelerometer.h"
#include "i2c.h"
#include <math.h> // Math library for trigonometric functions

//Linear acceleration is a measure of how quickly an object's velocity changes along a straight line (m/s²) rate of change of velocity
//Velocity = displacement (change of position)/ time interval
// MMA8451 accelerometer I2C address
#define MMA_ADDR (0x3A) 

// Register addresses for accelerometer data (high and low bytes for each axis)
// X-axis high byte
#define REG_XHI  (0x01) 
// X-axis low byte
#define REG_XLO  (0x02)
#define REG_YHI  (0x03)
#define REG_YLO  (0x04)
#define REG_ZHI	 (0x05)
#define REG_ZLO  (0x06)

// Control and identification register addresses
// WHO_AM_I register to verify device identity
#define REG_WHOAMI (0x0D) 
// Control register to set device configuration
#define REG_CTRL1  (0x2A)
// Control register 4 for additional configuration
#define REG_CTRL4  (0x2D)

// Expected device ID for MMA8451
#define WHOAMI     (0x1A)

// Conversion constants
// Accelerometer sensitivity: counts per g (gravity unit)
#define COUNTS_PER_G (4096.0)
#define M_PI         (3.14159265)

// Global variables for storing accelerometer readings
// Raw data for X, Y, and Z axes
int16_t acc_X=0, acc_Y=0, acc_Z=0;
// Calculated roll and pitch angles
float roll = 0.0, pitch = 0.0;

/*
 * @name   Delay
 * @brief  Function for delay
 *
 * Function for delay
 *
 * @param  uint32_t dlyTicks
 * @return void
 */
void Delay (uint32_t dly)
{
  volatile uint32_t t; // Volatile ensures the loop isn't optimized out

	for (t=dly*10000; t>0; t--)
		;
}

/*
 * @name   init_mma
 * @brief  Initializes the accelerometer
 *
 * Initializes the accelerometer: Configures the MMA8451 accelerometer by writing to its control register. 
 * This sets the accelerometer in active mode with 14-bit samples and an output data rate of 800 Hz.
 *
 * @param  void
 * @return int
 */
int init_mma()
{
	// Set the accelerometer to active mode, with 14-bit samples and 800 Hz O data rate
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/*
 * @name   read_full_xyz
 * @brief  Read raw readings from accelerometer
 *
 * Initiates an I2C transaction to read the accelerometer's data registers for the X, Y, and Z axes.
 * Each axis reading consists of a high and low byte, which are combined to form a 14-bit value.
 * The raw data is stored in global variables for later processing.
 *
 * @param  void
 * @return void
 */
void read_full_xyz()
{
	/*Uses I2C to read 6 bytes from the accelerometer (high and low bytes for each of X, Y, Z).
Combines these bytes to form 16-bit signed values, then adjusts for the 14-bit resolution of the accelerometer by dividing by 4.*/
	int i;
	uint8_t data[6]; // Array to store 6 bytes of raw accelerometer data
	int16_t temp[3]; // Temporary storage for 16-bit signed data for each axis

	i2c_start(); // Initiate I2C communication
	i2c_read_setup(MMA_ADDR , REG_XHI); // Start reading from the X-axis high byte register

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0); // Read byte without ending communication
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1); // Last read with stop condition

	// Combine high and low bytes for each axis to form 16-bit values
	for ( i=0; i<3; i++ ) {
		//Value=(High Byte<<8)∣Low Byte
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]); // Combine high and low bytes
	}

	// Adjust readings for 14-bit accelerometer data (divide by 4 to convert to actual value)
	// Align for 14 bits
	//2^16/2^14 = 4
	acc_X = temp[0]/4; // X-axis adjusted reading
	acc_Y = temp[1]/4; // Y-axis adjusted reading
	acc_Z = temp[2]/4; // Z-axis adjusted reading
}

/*
 * @name   convert_xyz_to_roll
 * @brief  Calculates the roll angle from readings
 *
 *  This function uses the accelerometer data to calculate the roll angle
 * of the device based on the arctangent of the Y and Z axis readings.
 * It also calculates the pitch angle for additional orientation information.
 *
 * @param  void
 * @return float roll
 */
float convert_xyz_to_roll()
{
	// Convert raw accelerometer data to g-units by dividing by COUNTS_PER_G; axis in g-units
	float ax = acc_X/COUNTS_PER_G,
	      ay = acc_Y/COUNTS_PER_G,
	      az = acc_Z/COUNTS_PER_G;

	// Calculate roll angle (rotation around X-axis) in degrees
	roll = atan2(ay, az)*180/M_PI;
	// Calculate pitch angle (rotation around Y-axis) in degrees
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;
	return roll; // Return roll angle as the primary output
}
