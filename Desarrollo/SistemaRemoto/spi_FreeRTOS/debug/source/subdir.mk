################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/aldaron/Documents/Workspace/Kinetis/SDK/boards/frdmkl27z/rtos_examples/freertos_spi/freertos_spi.c 

OBJS += \
./source/freertos_spi.o 

C_DEPS += \
./source/freertos_spi.d 


# Each subdirectory must supply rules for building sources it contributes
source/freertos_spi.o: /home/aldaron/Documents/Workspace/Kinetis/SDK/boards/frdmkl27z/rtos_examples/freertos_spi/freertos_spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g -DDEBUG -DCPU_MKL27Z64VLH4 -DFSL_RTOS_FREE_RTOS -DFRDM_KL27Z -DFREEDOM -I../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/ARM_CM0 -I../../../../../../rtos/freertos_9.0.0/Source/include -I../../../../../../CMSIS/Include -I../../../../../../devices -I../../../../../../devices/MKL27Z644/drivers -I../.. -I../../../../../../devices/MKL27Z644/utilities -I../../../../../../rtos/freertos_9.0.0/Source -I../../../.. -I../../../../../../devices/MKL27Z644 -std=gnu99 -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


