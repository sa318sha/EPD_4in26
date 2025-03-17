################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/ButtonDriver.cpp \
../Core/Src/Debug.cpp \
../Core/Src/EPD_4in26.cpp \
../Core/Src/EPD_test.cpp \
../Core/Src/FrameBuffer.cpp \
../Core/Src/FreeRTOSMemory.cpp \
../Core/Src/Rectangle.cpp \
../Core/Src/Screen.cpp \
../Core/Src/ScreenManager.cpp \
../Core/Src/main.cpp 

C_SRCS += \
../Core/Src/app_freertos.c \
../Core/Src/main.c \
../Core/Src/stm32wbxx_hal_msp.c \
../Core/Src/stm32wbxx_hal_timebase_tim.c \
../Core/Src/stm32wbxx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32wbxx.c 

C_DEPS += \
./Core/Src/app_freertos.d \
./Core/Src/main.d \
./Core/Src/stm32wbxx_hal_msp.d \
./Core/Src/stm32wbxx_hal_timebase_tim.d \
./Core/Src/stm32wbxx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32wbxx.d 

OBJS += \
./Core/Src/ButtonDriver.o \
./Core/Src/Debug.o \
./Core/Src/EPD_4in26.o \
./Core/Src/EPD_test.o \
./Core/Src/FrameBuffer.o \
./Core/Src/FreeRTOSMemory.o \
./Core/Src/Rectangle.o \
./Core/Src/Screen.o \
./Core/Src/ScreenManager.o \
./Core/Src/app_freertos.o \
./Core/Src/main.o \
./Core/Src/stm32wbxx_hal_msp.o \
./Core/Src/stm32wbxx_hal_timebase_tim.o \
./Core/Src/stm32wbxx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32wbxx.o 

CPP_DEPS += \
./Core/Src/ButtonDriver.d \
./Core/Src/Debug.d \
./Core/Src/EPD_4in26.d \
./Core/Src/EPD_test.d \
./Core/Src/FrameBuffer.d \
./Core/Src/FreeRTOSMemory.d \
./Core/Src/Rectangle.d \
./Core/Src/Screen.d \
./Core/Src/ScreenManager.d \
./Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_BSP_COM_FEATURE=1 -DUSE_COM_LOG=1 -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/P-NUCLEO-WB55.Nucleo -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_BSP_COM_FEATURE=1 -DUSE_COM_LOG=1 -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/P-NUCLEO-WB55.Nucleo -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ButtonDriver.cyclo ./Core/Src/ButtonDriver.d ./Core/Src/ButtonDriver.o ./Core/Src/ButtonDriver.su ./Core/Src/Debug.cyclo ./Core/Src/Debug.d ./Core/Src/Debug.o ./Core/Src/Debug.su ./Core/Src/EPD_4in26.cyclo ./Core/Src/EPD_4in26.d ./Core/Src/EPD_4in26.o ./Core/Src/EPD_4in26.su ./Core/Src/EPD_test.cyclo ./Core/Src/EPD_test.d ./Core/Src/EPD_test.o ./Core/Src/EPD_test.su ./Core/Src/FrameBuffer.cyclo ./Core/Src/FrameBuffer.d ./Core/Src/FrameBuffer.o ./Core/Src/FrameBuffer.su ./Core/Src/FreeRTOSMemory.cyclo ./Core/Src/FreeRTOSMemory.d ./Core/Src/FreeRTOSMemory.o ./Core/Src/FreeRTOSMemory.su ./Core/Src/Rectangle.cyclo ./Core/Src/Rectangle.d ./Core/Src/Rectangle.o ./Core/Src/Rectangle.su ./Core/Src/Screen.cyclo ./Core/Src/Screen.d ./Core/Src/Screen.o ./Core/Src/Screen.su ./Core/Src/ScreenManager.cyclo ./Core/Src/ScreenManager.d ./Core/Src/ScreenManager.o ./Core/Src/ScreenManager.su ./Core/Src/app_freertos.cyclo ./Core/Src/app_freertos.d ./Core/Src/app_freertos.o ./Core/Src/app_freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32wbxx_hal_msp.cyclo ./Core/Src/stm32wbxx_hal_msp.d ./Core/Src/stm32wbxx_hal_msp.o ./Core/Src/stm32wbxx_hal_msp.su ./Core/Src/stm32wbxx_hal_timebase_tim.cyclo ./Core/Src/stm32wbxx_hal_timebase_tim.d ./Core/Src/stm32wbxx_hal_timebase_tim.o ./Core/Src/stm32wbxx_hal_timebase_tim.su ./Core/Src/stm32wbxx_it.cyclo ./Core/Src/stm32wbxx_it.d ./Core/Src/stm32wbxx_it.o ./Core/Src/stm32wbxx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32wbxx.cyclo ./Core/Src/system_stm32wbxx.d ./Core/Src/system_stm32wbxx.o ./Core/Src/system_stm32wbxx.su

.PHONY: clean-Core-2f-Src

