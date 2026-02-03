################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/platform.c \
../platform/platform_i2c.c \
../platform/platform_spi.c \
../platform/platform_system.c 

OBJS += \
./platform/platform.o \
./platform/platform_i2c.o \
./platform/platform_spi.o \
./platform/platform_system.o 

C_DEPS += \
./platform/platform.d \
./platform/platform_i2c.d \
./platform/platform_spi.d \
./platform/platform_system.d 


# Each subdirectory must supply rules for building sources it contributes
platform/%.o platform/%.su platform/%.cyclo: ../platform/%.c platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/manhhai/Desktop/test_gimbal_v4_spi_i2c/drvs/Inc" -I"/home/manhhai/Desktop/test_gimbal_v4_spi_i2c/platform/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-platform

clean-platform:
	-$(RM) ./platform/platform.cyclo ./platform/platform.d ./platform/platform.o ./platform/platform.su ./platform/platform_i2c.cyclo ./platform/platform_i2c.d ./platform/platform_i2c.o ./platform/platform_i2c.su ./platform/platform_spi.cyclo ./platform/platform_spi.d ./platform/platform_spi.o ./platform/platform_spi.su ./platform/platform_system.cyclo ./platform/platform_system.d ./platform/platform_system.o ./platform/platform_system.su

.PHONY: clean-platform

