################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../startup/startup_mk66f18.cpp 

OBJS += \
./startup/startup_mk66f18.o 

CPP_DEPS += \
./startup/startup_mk66f18.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++17 -DCPU_MK66FX1M0VLQ18 -DCPU_MK66FX1M0VLQ18_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../board -I../source -I../source/module -I../HITSIC/utilities -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/inc -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/plugins/types -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/plugins/types/struct2json/inc -I../HITSIC/d_mk66f18 -I../HITSIC/d_mk66f18/legacy_drivers -I../HITSIC/d_mk66f18/extlib_port/EasyFlash-4.0.0/easyflash/port -I../ -I../amazon-freertos/freertos/portable -I../amazon-freertos/include -I../drivers -I../device -I../CMSIS -I../drivers/freertos -I../component/lists -I../component/serial_manager -I../utilities -I../component/uart -I../usb/include -I../osa -I../usb/phy -I../usb/device/class -I../usb/device/include -I../usb/device/source -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source/generated -I../usb/host/class -I../usb/host -I../fatfs -I../fatfs/fatfs_include -I../sdmmc/inc -I../sdmmc/port -I../component/serial_manager/usb_cdc_adapter -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -frtti -fexceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


