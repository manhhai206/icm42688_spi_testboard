################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drvs/icm42688_i2c.c \
../drvs/icm42688_spi.c 

OBJS += \
./drvs/icm42688_i2c.o \
./drvs/icm42688_spi.o 

C_DEPS += \
./drvs/icm42688_i2c.d \
./drvs/icm42688_spi.d 


# Each subdirectory must supply rules for building sources it contributes
drvs/%.o drvs/%.su drvs/%.cyclo: ../drvs/%.c drvs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/manhhai/Desktop/test_gimbal_v4_spi_i2c/drvs/Inc" -I"/home/manhhai/Desktop/test_gimbal_v4_spi_i2c/platform/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drvs

clean-drvs:
	-$(RM) ./drvs/icm42688_i2c.cyclo ./drvs/icm42688_i2c.d ./drvs/icm42688_i2c.o ./drvs/icm42688_i2c.su ./drvs/icm42688_spi.cyclo ./drvs/icm42688_spi.d ./drvs/icm42688_spi.o ./drvs/icm42688_spi.su

.PHONY: clean-drvs

