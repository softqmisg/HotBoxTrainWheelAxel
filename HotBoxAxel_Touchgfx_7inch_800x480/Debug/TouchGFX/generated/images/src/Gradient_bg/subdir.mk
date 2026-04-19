################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/Gradient_bg/image_midday.cpp \
../TouchGFX/generated/images/src/Gradient_bg/image_midday1.cpp \
../TouchGFX/generated/images/src/Gradient_bg/image_night.cpp \
../TouchGFX/generated/images/src/Gradient_bg/image_night_large.cpp 

OBJS += \
./TouchGFX/generated/images/src/Gradient_bg/image_midday.o \
./TouchGFX/generated/images/src/Gradient_bg/image_midday1.o \
./TouchGFX/generated/images/src/Gradient_bg/image_night.o \
./TouchGFX/generated/images/src/Gradient_bg/image_night_large.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/Gradient_bg/image_midday.d \
./TouchGFX/generated/images/src/Gradient_bg/image_midday1.d \
./TouchGFX/generated/images/src/Gradient_bg/image_night.d \
./TouchGFX/generated/images/src/Gradient_bg/image_night_large.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/Gradient_bg/%.o TouchGFX/generated/images/src/Gradient_bg/%.su TouchGFX/generated/images/src/Gradient_bg/%.cyclo: ../TouchGFX/generated/images/src/Gradient_bg/%.cpp TouchGFX/generated/images/src/Gradient_bg/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DUSE_PWR_LDO_SUPPLY -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I"E:/Mehdi_Other/NowFan/FSK/Application/HotBoxTrainWheelAxel/HotBoxAxel_Touchgfx_7inch_800x480/Core/CPT_TOUCH/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-Gradient_bg

clean-TouchGFX-2f-generated-2f-images-2f-src-2f-Gradient_bg:
	-$(RM) ./TouchGFX/generated/images/src/Gradient_bg/image_midday.cyclo ./TouchGFX/generated/images/src/Gradient_bg/image_midday.d ./TouchGFX/generated/images/src/Gradient_bg/image_midday.o ./TouchGFX/generated/images/src/Gradient_bg/image_midday.su ./TouchGFX/generated/images/src/Gradient_bg/image_midday1.cyclo ./TouchGFX/generated/images/src/Gradient_bg/image_midday1.d ./TouchGFX/generated/images/src/Gradient_bg/image_midday1.o ./TouchGFX/generated/images/src/Gradient_bg/image_midday1.su ./TouchGFX/generated/images/src/Gradient_bg/image_night.cyclo ./TouchGFX/generated/images/src/Gradient_bg/image_night.d ./TouchGFX/generated/images/src/Gradient_bg/image_night.o ./TouchGFX/generated/images/src/Gradient_bg/image_night.su ./TouchGFX/generated/images/src/Gradient_bg/image_night_large.cyclo ./TouchGFX/generated/images/src/Gradient_bg/image_night_large.d ./TouchGFX/generated/images/src/Gradient_bg/image_night_large.o ./TouchGFX/generated/images/src/Gradient_bg/image_night_large.su

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src-2f-Gradient_bg

