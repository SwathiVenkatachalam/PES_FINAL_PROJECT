################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/accelerometer.c \
../source/adc.c \
../source/adc_calibrate.c \
../source/autocorrelate.c \
../source/commandhandler.c \
../source/commandprocessor.c \
../source/dac.c \
../source/dma.c \
../source/i2c.c \
../source/led.c \
../source/main.c \
../source/mtb.c \
../source/musical_tones.c \
../source/queue.c \
../source/semihost_hardfault.c \
../source/sysclock.c \
../source/systick.c \
../source/test_queue.c \
../source/test_sine.c \
../source/tone_to_sample.c \
../source/tpm.c \
../source/uart.c 

C_DEPS += \
./source/accelerometer.d \
./source/adc.d \
./source/adc_calibrate.d \
./source/autocorrelate.d \
./source/commandhandler.d \
./source/commandprocessor.d \
./source/dac.d \
./source/dma.d \
./source/i2c.d \
./source/led.d \
./source/main.d \
./source/mtb.d \
./source/musical_tones.d \
./source/queue.d \
./source/semihost_hardfault.d \
./source/sysclock.d \
./source/systick.d \
./source/test_queue.d \
./source/test_sine.d \
./source/tone_to_sample.d \
./source/tpm.d \
./source/uart.d 

OBJS += \
./source/accelerometer.o \
./source/adc.o \
./source/adc_calibrate.o \
./source/autocorrelate.o \
./source/commandhandler.o \
./source/commandprocessor.o \
./source/dac.o \
./source/dma.o \
./source/i2c.o \
./source/led.o \
./source/main.o \
./source/mtb.o \
./source/musical_tones.o \
./source/queue.o \
./source/semihost_hardfault.o \
./source/sysclock.o \
./source/systick.o \
./source/test_queue.o \
./source/test_sine.o \
./source/tone_to_sample.o \
./source/tpm.o \
./source/uart.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Swathi Venkatachalam\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Musical-Notes-Player-SwathiVenkatachalam\board" -I"C:\Users\Swathi Venkatachalam\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Musical-Notes-Player-SwathiVenkatachalam\source" -I"C:\Users\Swathi Venkatachalam\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Musical-Notes-Player-SwathiVenkatachalam" -I"C:\Users\Swathi Venkatachalam\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Musical-Notes-Player-SwathiVenkatachalam\drivers" -I"C:\Users\Swathi Venkatachalam\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Musical-Notes-Player-SwathiVenkatachalam\CMSIS" -I"C:\Users\Swathi Venkatachalam\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Musical-Notes-Player-SwathiVenkatachalam\utilities" -I"C:\Users\Swathi Venkatachalam\Documents\MCUXpressoIDE_11.6.0_8187\workspace\Musical-Notes-Player-SwathiVenkatachalam\startup" -O0 -fno-common -g3 -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/accelerometer.d ./source/accelerometer.o ./source/adc.d ./source/adc.o ./source/adc_calibrate.d ./source/adc_calibrate.o ./source/autocorrelate.d ./source/autocorrelate.o ./source/commandhandler.d ./source/commandhandler.o ./source/commandprocessor.d ./source/commandprocessor.o ./source/dac.d ./source/dac.o ./source/dma.d ./source/dma.o ./source/i2c.d ./source/i2c.o ./source/led.d ./source/led.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/musical_tones.d ./source/musical_tones.o ./source/queue.d ./source/queue.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sysclock.d ./source/sysclock.o ./source/systick.d ./source/systick.o ./source/test_queue.d ./source/test_queue.o ./source/test_sine.d ./source/test_sine.o ./source/tone_to_sample.d ./source/tone_to_sample.o ./source/tpm.d ./source/tpm.o ./source/uart.d ./source/uart.o

.PHONY: clean-source

