/*
 * @file        i2c.h
 * @brief       Initialization of I2C functions for MMA accelerometer
 *
 * Initialization of LED function declarations
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @reference   https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/inc/i2c.h
 *
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

/*
 * @name   init_i2c
 * @brief  Initializes I2C
 *
 * Initializes RGB
 *
 * @param  none
 * @return void
 */
void init_i2c();

/*
 * @name   i2c_start
 * @brief  Send start sequence
 *
 * Send start sequence
 *
 * @param  none
 * @return void
 */
void i2c_start();

/*
 * @name   i2c_read_setup
 * @brief  Send device and register address
 *
 * Send device and register address
 *
 * @param  uint8_t dev, uint8_t address
 * @return void
 */
void i2c_read_setup(uint8_t dev, uint8_t address);

/*
 * @name   i2c_repeated_read
 * @brief  Read a byte and ack/ nack as appropriate
 *
 * Initializes RGB
 *
 * @param  uint8_t isLastRead
 * @return void
 */
uint8_t i2c_repeated_read(uint8_t);

/*
 * @name   i2c_read_byte
 * @brief  Reads a byte data to dev address
 *
 * Reads a byte data to dev address using 7 but addressing
 *
 * @param  uint8_t dev, uint8_t address
 * @return void
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);

/*
 * @name   i2c_write_byte
 * @brief  Writes a byte data to dev address
 *
 * Writes a byte data to dev address using 7 but addressing
 *
 * @param  uint8_t dev, uint8_t address, uint8_t data
 * @return void
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* I2C_H_ */
