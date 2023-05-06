/*
 * @file        accelerometer.h
 * @brief       Functions for MMA8451 accelerometer
 *
 * Functions for MMA8451 accelerometer
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references  https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/inc/mma8451.h
 *
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <stdint.h>

/*
 * @name   Delay
 * @brief  Function for delay
 *
 * Function for delay
 *
 * @param  uint32_t dlyTicks
 * @return void
 */
void Delay(uint32_t dlyTicks);

/*
 * @name   init_mma
 * @brief  Initializes the accelerometer
 *
 * Initializes the accelerometer
 *
 * @param  void
 * @return int
 */
int init_mma();

/*
 * @name   read_full_xyz
 * @brief  Read raw readings from accelerometer
 *
 * Read raw readings from accelerometer
 *
 * @param  void
 * @return void
 */
void read_full_xyz();

/*
 * @name   convert_xyz_to_roll
 * @brief  Calculates the roll angle from readings
 *
 * Calculates the roll angle from readings
 *
 * @param  void
 * @return float roll
 */
float convert_xyz_to_roll();

#endif /* ACCELEROMETER_H_ */
