/*
 * @file        adc_calibrate.c
 * @brief       Function Implementation of adc calibrate function, which is declared in adc.h
 *
 * Contains ADC calibrate function
 *
 * @author      Swathi Venkatachalam
 * @tools       MCUXpresso IDE
 * @references  KL25Z Reference Manual 28.4.6 Calibration Function
 *
 */

#include <stdio.h>
#include <fsl_debug_console.h>

#include "adc.h"

#include "MKL25Z4.h"

#define INIT    (0)      //initialize calibrate variable to 0 for minus side
#define TWO     (2)      //divide by 2 in calibrate function
#define SET_MSB (0x8000) //set MSB of calibrate variable

/*
 * @name   calibrate_ADC
 * @brief  Function calibrates ADC0
 *
 * 1. Initialize or clear a 16-bit variable in RAM.
 * 2. Add the plus-side calibration results CLP0, CLP1, CLP2, CLP3, CLP4, and CLPS to the variable.
 * 3. Divide the variable by two.
 * 4. Set the MSB of the variable.
 * 5. The previous two steps can be achieved by setting the carry bit, rotating to the right through the carry bit on the high byte and again on the low byte.
 * 6. Store the value in the plus-side gain calibration register PG.
 * 7. Repeat the procedure for the minus-side gain calibration value.
 *
 * @param  void
 * @return void
 */

void calibrate_ADC()
{
    //1. set ADC calibration flag
    ADC0->SC3 |= ADC_SC3_CAL_MASK;

    //2. Add the plus-side calibration results CLP0, CLP1, CLP2, CLP3, CLP4, and CLPS to the variable.
    uint16_t calibrate = ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4 + ADC0->CLPS;

    //3.  Divide the variable by two.
    calibrate = calibrate / TWO;

    //4. Set the MSB of the variable
    calibrate = calibrate + SET_MSB;

    //5. Store the value in the plus-side gain calibration register PG
    ADC0->PG = calibrate;

    // 6. Repeat the procedure for the minus-side gain calibration value.
    calibrate = INIT;

    //6.2. Add the minus-side calibration results CLP0, CLP1, CLP2, CLP3, CLP4, and CLPS to the variable.
    calibrate = ADC0->CLM0 + ADC0->CLM1 + ADC0->CLM2 + ADC0->CLM3 + ADC0->CLM4 + ADC0->CLMS;

    //6.3.  Divide the variable by two.
    calibrate = calibrate / TWO;

    //6.4. Set the MSB of the variable
    calibrate = calibrate + SET_MSB;

    //6.5. Store the value in the minus-side gain calibration register PG
    ADC0->MG = calibrate;
}
