################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/src/subdir.mk
-include HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/plugins/types/struct2json/src/subdir.mk
-include HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/plugins/types/subdir.mk
-include HITSIC/utilities/subdir.mk
-include HITSIC/d_mk66f18/extlib_port/EasyFlash-4.0.0/easyflash/port/subdir.mk
-include HITSIC/d_mk66f18/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: HITSIC_MK66F18_MCUX.axf

# Tool invocations
HITSIC_MK66F18_MCUX.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"C:\Users\CkovMk\Repository\HTISIC_MK66F18\HITSIC_MK66F18_MCUX\libs" -Xlinker -Map="HITSIC_MK66F18_MCUX.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T "HITSIC_MK66F18_MCUX_Debug.ld" -o "HITSIC_MK66F18_MCUX.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) HITSIC_MK66F18_MCUX.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "HITSIC_MK66F18_MCUX.axf" ; rm ../Debug/HITSIC_MK66F18_MCUX.map ; # arm-none-eabi-objcopy -v -O binary "HITSIC_MK66F18_MCUX.axf" "HITSIC_MK66F18_MCUX.bin" ; # checksum -p MK66FX1M0xxx18 -d "HITSIC_MK66F18_MCUX.bin"
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
