################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/menuscreen_screen/MenuScreenPresenter.cpp \
../TouchGFX/gui/src/menuscreen_screen/MenuScreenView.cpp 

OBJS += \
./TouchGFX/gui/src/menuscreen_screen/MenuScreenPresenter.o \
./TouchGFX/gui/src/menuscreen_screen/MenuScreenView.o 

CPP_DEPS += \
./TouchGFX/gui/src/menuscreen_screen/MenuScreenPresenter.d \
./TouchGFX/gui/src/menuscreen_screen/MenuScreenView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/menuscreen_screen/%.o TouchGFX/gui/src/menuscreen_screen/%.su: ../TouchGFX/gui/src/menuscreen_screen/%.cpp TouchGFX/gui/src/menuscreen_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/gui/include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I"C:/Users/mordo/STM32CubeIDE/workspace_1.7.0/meteo_tgfx/Touchscreen" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/mordo/STM32CubeIDE/workspace_1.7.0/meteo_tgfx/Climate" -I"C:/Users/mordo/STM32CubeIDE/workspace_1.7.0/meteo_tgfx/esp" -I"C:/Users/mordo/STM32CubeIDE/workspace_1.7.0/meteo_tgfx/protobuf" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-menuscreen_screen

clean-TouchGFX-2f-gui-2f-src-2f-menuscreen_screen:
	-$(RM) ./TouchGFX/gui/src/menuscreen_screen/MenuScreenPresenter.d ./TouchGFX/gui/src/menuscreen_screen/MenuScreenPresenter.o ./TouchGFX/gui/src/menuscreen_screen/MenuScreenPresenter.su ./TouchGFX/gui/src/menuscreen_screen/MenuScreenView.d ./TouchGFX/gui/src/menuscreen_screen/MenuScreenView.o ./TouchGFX/gui/src/menuscreen_screen/MenuScreenView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-menuscreen_screen

