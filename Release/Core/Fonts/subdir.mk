################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Fonts/font12.cpp \
../Core/Fonts/font16.cpp \
../Core/Fonts/font20.cpp \
../Core/Fonts/font24.cpp \
../Core/Fonts/font8.cpp 

OBJS += \
./Core/Fonts/font12.o \
./Core/Fonts/font16.o \
./Core/Fonts/font20.o \
./Core/Fonts/font24.o \
./Core/Fonts/font8.o 

CPP_DEPS += \
./Core/Fonts/font12.d \
./Core/Fonts/font16.d \
./Core/Fonts/font20.d \
./Core/Fonts/font24.d \
./Core/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Fonts/%.o Core/Fonts/%.su Core/Fonts/%.cyclo: ../Core/Fonts/%.cpp Core/Fonts/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_NUCLEO_64 -DUSE_BSP_COM_FEATURE=1 -DUSE_COM_LOG=1 -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/P-NUCLEO-WB55.Nucleo -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Fonts

clean-Core-2f-Fonts:
	-$(RM) ./Core/Fonts/font12.cyclo ./Core/Fonts/font12.d ./Core/Fonts/font12.o ./Core/Fonts/font12.su ./Core/Fonts/font16.cyclo ./Core/Fonts/font16.d ./Core/Fonts/font16.o ./Core/Fonts/font16.su ./Core/Fonts/font20.cyclo ./Core/Fonts/font20.d ./Core/Fonts/font20.o ./Core/Fonts/font20.su ./Core/Fonts/font24.cyclo ./Core/Fonts/font24.d ./Core/Fonts/font24.o ./Core/Fonts/font24.su ./Core/Fonts/font8.cyclo ./Core/Fonts/font8.d ./Core/Fonts/font8.o ./Core/Fonts/font8.su

.PHONY: clean-Core-2f-Fonts

