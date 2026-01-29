################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drvs/gpio_drv.c \
../drvs/i2c_drv.c \
../drvs/icm42688_i2c_drv.c \
../drvs/icm42688_spi_drv.c \
../drvs/spi_drv.c 

OBJS += \
./drvs/gpio_drv.o \
./drvs/i2c_drv.o \
./drvs/icm42688_i2c_drv.o \
./drvs/icm42688_spi_drv.o \
./drvs/spi_drv.o 

C_DEPS += \
./drvs/gpio_drv.d \
./drvs/i2c_drv.d \
./drvs/icm42688_i2c_drv.d \
./drvs/icm42688_spi_drv.d \
./drvs/spi_drv.d 


# Each subdirectory must supply rules for building sources it contributes
drvs/%.o drvs/%.su drvs/%.cyclo: ../drvs/%.c drvs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/manhhai/Desktop/test_gimbal_v4_spi_i2c/drvs/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drvs

clean-drvs:
	-$(RM) ./drvs/gpio_drv.cyclo ./drvs/gpio_drv.d ./drvs/gpio_drv.o ./drvs/gpio_drv.su ./drvs/i2c_drv.cyclo ./drvs/i2c_drv.d ./drvs/i2c_drv.o ./drvs/i2c_drv.su ./drvs/icm42688_i2c_drv.cyclo ./drvs/icm42688_i2c_drv.d ./drvs/icm42688_i2c_drv.o ./drvs/icm42688_i2c_drv.su ./drvs/icm42688_spi_drv.cyclo ./drvs/icm42688_spi_drv.d ./drvs/icm42688_spi_drv.o ./drvs/icm42688_spi_drv.su ./drvs/spi_drv.cyclo ./drvs/spi_drv.d ./drvs/spi_drv.o ./drvs/spi_drv.su

.PHONY: clean-drvs

