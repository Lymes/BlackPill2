################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Lcd/Fonts/font12.c \
../Core/Src/Lcd/Fonts/font16.c \
../Core/Src/Lcd/Fonts/font20.c \
../Core/Src/Lcd/Fonts/font24.c \
../Core/Src/Lcd/Fonts/font8.c 

OBJS += \
./Core/Src/Lcd/Fonts/font12.o \
./Core/Src/Lcd/Fonts/font16.o \
./Core/Src/Lcd/Fonts/font20.o \
./Core/Src/Lcd/Fonts/font24.o \
./Core/Src/Lcd/Fonts/font8.o 

C_DEPS += \
./Core/Src/Lcd/Fonts/font12.d \
./Core/Src/Lcd/Fonts/font16.d \
./Core/Src/Lcd/Fonts/font20.d \
./Core/Src/Lcd/Fonts/font24.d \
./Core/Src/Lcd/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Lcd/Fonts/font12.o: ../Core/Src/Lcd/Fonts/font12.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Src/Lcd -I../USB_DEVICE/Target -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core_A/Include/ -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core/Include/ -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Core/Src/w25qxx -I../USB_DEVICE/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Lcd/Fonts/font12.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Lcd/Fonts/font16.o: ../Core/Src/Lcd/Fonts/font16.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Src/Lcd -I../USB_DEVICE/Target -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core_A/Include/ -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core/Include/ -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Core/Src/w25qxx -I../USB_DEVICE/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Lcd/Fonts/font16.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Lcd/Fonts/font20.o: ../Core/Src/Lcd/Fonts/font20.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Src/Lcd -I../USB_DEVICE/Target -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core_A/Include/ -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core/Include/ -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Core/Src/w25qxx -I../USB_DEVICE/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Lcd/Fonts/font20.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Lcd/Fonts/font24.o: ../Core/Src/Lcd/Fonts/font24.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Src/Lcd -I../USB_DEVICE/Target -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core_A/Include/ -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core/Include/ -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Core/Src/w25qxx -I../USB_DEVICE/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Lcd/Fonts/font24.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Lcd/Fonts/font8.o: ../Core/Src/Lcd/Fonts/font8.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Core/Src/Lcd -I../USB_DEVICE/Target -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core_A/Include/ -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS//CMSIS/Core/Include/ -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Core/Src/w25qxx -I../USB_DEVICE/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Lcd/Fonts/font8.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

