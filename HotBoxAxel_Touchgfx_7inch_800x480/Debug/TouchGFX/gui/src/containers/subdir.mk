################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/containers/BottomBar.cpp \
../TouchGFX/gui/src/containers/CarSelector.cpp \
../TouchGFX/gui/src/containers/Keyboard.cpp \
../TouchGFX/gui/src/containers/Led.cpp \
../TouchGFX/gui/src/containers/SliderWithLabel.cpp \
../TouchGFX/gui/src/containers/SpinBox.cpp \
../TouchGFX/gui/src/containers/TempAxel.cpp \
../TouchGFX/gui/src/containers/TempAxelList.cpp \
../TouchGFX/gui/src/containers/TopBar.cpp \
../TouchGFX/gui/src/containers/WarningBar.cpp \
../TouchGFX/gui/src/containers/passwordPopup.cpp 

OBJS += \
./TouchGFX/gui/src/containers/BottomBar.o \
./TouchGFX/gui/src/containers/CarSelector.o \
./TouchGFX/gui/src/containers/Keyboard.o \
./TouchGFX/gui/src/containers/Led.o \
./TouchGFX/gui/src/containers/SliderWithLabel.o \
./TouchGFX/gui/src/containers/SpinBox.o \
./TouchGFX/gui/src/containers/TempAxel.o \
./TouchGFX/gui/src/containers/TempAxelList.o \
./TouchGFX/gui/src/containers/TopBar.o \
./TouchGFX/gui/src/containers/WarningBar.o \
./TouchGFX/gui/src/containers/passwordPopup.o 

CPP_DEPS += \
./TouchGFX/gui/src/containers/BottomBar.d \
./TouchGFX/gui/src/containers/CarSelector.d \
./TouchGFX/gui/src/containers/Keyboard.d \
./TouchGFX/gui/src/containers/Led.d \
./TouchGFX/gui/src/containers/SliderWithLabel.d \
./TouchGFX/gui/src/containers/SpinBox.d \
./TouchGFX/gui/src/containers/TempAxel.d \
./TouchGFX/gui/src/containers/TempAxelList.d \
./TouchGFX/gui/src/containers/TopBar.d \
./TouchGFX/gui/src/containers/WarningBar.d \
./TouchGFX/gui/src/containers/passwordPopup.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/containers/%.o TouchGFX/gui/src/containers/%.su TouchGFX/gui/src/containers/%.cyclo: ../TouchGFX/gui/src/containers/%.cpp TouchGFX/gui/src/containers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -DUSE_PWR_LDO_SUPPLY -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I"C:/Users/alire/Desktop/Mofidi/HotBoxTrainWheelAxel/HotBoxAxel_Touchgfx_7inch_800x480/Core/CPT_TOUCH/Inc" -I"C:/Users/alire/Desktop/Mofidi/HotBoxTrainWheelAxel/HotBoxAxel_Touchgfx_7inch_800x480/Core/CustomClasses/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-containers

clean-TouchGFX-2f-gui-2f-src-2f-containers:
	-$(RM) ./TouchGFX/gui/src/containers/BottomBar.cyclo ./TouchGFX/gui/src/containers/BottomBar.d ./TouchGFX/gui/src/containers/BottomBar.o ./TouchGFX/gui/src/containers/BottomBar.su ./TouchGFX/gui/src/containers/CarSelector.cyclo ./TouchGFX/gui/src/containers/CarSelector.d ./TouchGFX/gui/src/containers/CarSelector.o ./TouchGFX/gui/src/containers/CarSelector.su ./TouchGFX/gui/src/containers/Keyboard.cyclo ./TouchGFX/gui/src/containers/Keyboard.d ./TouchGFX/gui/src/containers/Keyboard.o ./TouchGFX/gui/src/containers/Keyboard.su ./TouchGFX/gui/src/containers/Led.cyclo ./TouchGFX/gui/src/containers/Led.d ./TouchGFX/gui/src/containers/Led.o ./TouchGFX/gui/src/containers/Led.su ./TouchGFX/gui/src/containers/SliderWithLabel.cyclo ./TouchGFX/gui/src/containers/SliderWithLabel.d ./TouchGFX/gui/src/containers/SliderWithLabel.o ./TouchGFX/gui/src/containers/SliderWithLabel.su ./TouchGFX/gui/src/containers/SpinBox.cyclo ./TouchGFX/gui/src/containers/SpinBox.d ./TouchGFX/gui/src/containers/SpinBox.o ./TouchGFX/gui/src/containers/SpinBox.su ./TouchGFX/gui/src/containers/TempAxel.cyclo ./TouchGFX/gui/src/containers/TempAxel.d ./TouchGFX/gui/src/containers/TempAxel.o ./TouchGFX/gui/src/containers/TempAxel.su ./TouchGFX/gui/src/containers/TempAxelList.cyclo ./TouchGFX/gui/src/containers/TempAxelList.d ./TouchGFX/gui/src/containers/TempAxelList.o ./TouchGFX/gui/src/containers/TempAxelList.su ./TouchGFX/gui/src/containers/TopBar.cyclo ./TouchGFX/gui/src/containers/TopBar.d ./TouchGFX/gui/src/containers/TopBar.o ./TouchGFX/gui/src/containers/TopBar.su ./TouchGFX/gui/src/containers/WarningBar.cyclo ./TouchGFX/gui/src/containers/WarningBar.d ./TouchGFX/gui/src/containers/WarningBar.o ./TouchGFX/gui/src/containers/WarningBar.su ./TouchGFX/gui/src/containers/passwordPopup.cyclo ./TouchGFX/gui/src/containers/passwordPopup.d ./TouchGFX/gui/src/containers/passwordPopup.o ./TouchGFX/gui/src/containers/passwordPopup.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-containers

