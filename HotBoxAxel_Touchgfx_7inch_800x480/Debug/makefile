################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include TouchGFX/target/generated/subdir.mk
-include TouchGFX/target/subdir.mk
-include TouchGFX/gui/src/settingscreen_screen/subdir.mk
-include TouchGFX/gui/src/model/subdir.mk
-include TouchGFX/gui/src/mainscreen_screen/subdir.mk
-include TouchGFX/gui/src/containers/subdir.mk
-include TouchGFX/gui/src/common/subdir.mk
-include TouchGFX/generated/texts/src/subdir.mk
-include TouchGFX/generated/images/src/__generated/subdir.mk
-include TouchGFX/generated/images/src/Gradient_bg/subdir.mk
-include TouchGFX/generated/images/src/subdir.mk
-include TouchGFX/generated/gui_generated/src/settingscreen_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/mainscreen_screen/subdir.mk
-include TouchGFX/generated/gui_generated/src/containers/subdir.mk
-include TouchGFX/generated/gui_generated/src/common/subdir.mk
-include TouchGFX/generated/fonts/src/subdir.mk
-include TouchGFX/App/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Inc/subdir.mk
-include Core/CPT_TOUCH/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := HotBoxAxel_Touchgfx_7inch_800x480
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
HotBoxAxel_Touchgfx_7inch_800x480.elf \

MAP_FILES += \
HotBoxAxel_Touchgfx_7inch_800x480.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
HotBoxAxel_Touchgfx_7inch_800x480.list \

OBJCOPY_HEX += \
HotBoxAxel_Touchgfx_7inch_800x480.hex \

OBJCOPY_BIN += \
HotBoxAxel_Touchgfx_7inch_800x480.bin \


# All Target
all: main-build

# Main-build Target
main-build: HotBoxAxel_Touchgfx_7inch_800x480.elf secondary-outputs

# Tool invocations
HotBoxAxel_Touchgfx_7inch_800x480.elf HotBoxAxel_Touchgfx_7inch_800x480.map: $(OBJS) $(USER_OBJS) E:\Mehdi_Other\NowFan\FSK\Application\HotBoxTrainWheelAxel\HotBoxAxel_Touchgfx_7inch_800x480\STM32H743IITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "HotBoxAxel_Touchgfx_7inch_800x480.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"E:\Mehdi_Other\NowFan\FSK\Application\HotBoxTrainWheelAxel\HotBoxAxel_Touchgfx_7inch_800x480\STM32H743IITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="HotBoxAxel_Touchgfx_7inch_800x480.map" -Wl,--gc-sections -static -L"E:\Mehdi_Other\NowFan\FSK\Application\HotBoxTrainWheelAxel\HotBoxAxel_Touchgfx_7inch_800x480\Middlewares\ST\touchgfx\lib\core\cortex_m7\gcc" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

HotBoxAxel_Touchgfx_7inch_800x480.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "HotBoxAxel_Touchgfx_7inch_800x480.list"
	@echo 'Finished building: $@'
	@echo ' '

HotBoxAxel_Touchgfx_7inch_800x480.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "HotBoxAxel_Touchgfx_7inch_800x480.hex"
	@echo 'Finished building: $@'
	@echo ' '

HotBoxAxel_Touchgfx_7inch_800x480.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "HotBoxAxel_Touchgfx_7inch_800x480.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) HotBoxAxel_Touchgfx_7inch_800x480.bin HotBoxAxel_Touchgfx_7inch_800x480.elf HotBoxAxel_Touchgfx_7inch_800x480.hex HotBoxAxel_Touchgfx_7inch_800x480.list HotBoxAxel_Touchgfx_7inch_800x480.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
