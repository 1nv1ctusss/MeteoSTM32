################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32h743xihx.s 

S_DEPS += \
./Core/Startup/startup_stm32h743xihx.d 

OBJS += \
./Core/Startup/startup_stm32h743xihx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32h743xihx.o: ../Core/Startup/startup_stm32h743xihx.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/gui/include -I"H:/SPELS/meteo_tgfx/Touchscreen" -I"H:/SPELS/meteo_tgfx/Climate" -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32h743xihx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

