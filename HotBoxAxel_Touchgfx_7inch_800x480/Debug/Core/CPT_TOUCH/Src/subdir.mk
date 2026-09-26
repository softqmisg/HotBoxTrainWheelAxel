################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/CPT_TOUCH/Src/touch_800x480.c \
../Core/CPT_TOUCH/Src/touch_iic.c 

C_DEPS += \
./Core/CPT_TOUCH/Src/touch_800x480.d \
./Core/CPT_TOUCH/Src/touch_iic.d 

OBJS += \
./Core/CPT_TOUCH/Src/touch_800x480.o \
./Core/CPT_TOUCH/Src/touch_iic.o 


# Each subdirectory must supply rules for building sources it contributes
Core/CPT_TOUCH/Src/%.o Core/CPT_TOUCH/Src/%.su Core/CPT_TOUCH/Src/%.cyclo: ../Core/CPT_TOUCH/Src/%.c Core/CPT_TOUCH/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DUSE_PWR_LDO_SUPPLY -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I"C:/Users/alire/Desktop/Mofidi/HotBoxTrainWheelAxel/HotBoxAxel_Touchgfx_7inch_800x480/Core/CPT_TOUCH/Inc" -I"C:/Users/alire/Desktop/Mofidi/HotBoxTrainWheelAxel/HotBoxAxel_Touchgfx_7inch_800x480/Core/CustomClasses/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-CPT_TOUCH-2f-Src

clean-Core-2f-CPT_TOUCH-2f-Src:
	-$(RM) ./Core/CPT_TOUCH/Src/touch_800x480.cyclo ./Core/CPT_TOUCH/Src/touch_800x480.d ./Core/CPT_TOUCH/Src/touch_800x480.o ./Core/CPT_TOUCH/Src/touch_800x480.su ./Core/CPT_TOUCH/Src/touch_iic.cyclo ./Core/CPT_TOUCH/Src/touch_iic.d ./Core/CPT_TOUCH/Src/touch_iic.o ./Core/CPT_TOUCH/Src/touch_iic.su

.PHONY: clean-Core-2f-CPT_TOUCH-2f-Src

