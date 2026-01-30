################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/app.c \
../app/icm42688.c \
../app/scheduler.c 

OBJS += \
./app/app.o \
./app/icm42688.o \
./app/scheduler.o 

C_DEPS += \
./app/app.d \
./app/icm42688.d \
./app/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o app/%.su app/%.cyclo: ../app/%.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/manhhai/Desktop/test_gimbal_v4_spi_i2c/app/Inc" -I"/home/manhhai/Desktop/test_gimbal_v4_spi_i2c/platform/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/app.cyclo ./app/app.d ./app/app.o ./app/app.su ./app/icm42688.cyclo ./app/icm42688.d ./app/icm42688.o ./app/icm42688.su ./app/scheduler.cyclo ./app/scheduler.d ./app/scheduler.o ./app/scheduler.su

.PHONY: clean-app

