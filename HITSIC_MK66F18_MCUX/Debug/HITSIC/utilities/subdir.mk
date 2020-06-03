################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HITSIC/utilities/sys_extint.cpp \
../HITSIC/utilities/sys_pitmgr.cpp \
../HITSIC/utilities/sys_uartmgr.cpp 

C_SRCS += \
../HITSIC/utilities/app_menu.c \
../HITSIC/utilities/app_menu_button.c \
../HITSIC/utilities/app_menu_nvm.c \
../HITSIC/utilities/app_menu_type.c \
../HITSIC/utilities/drv_button.c \
../HITSIC/utilities/drv_disp_ssd1306.c \
../HITSIC/utilities/drv_ftfx_flash.c \
../HITSIC/utilities/drv_imu_invensense.c \
../HITSIC/utilities/lib_list.c \
../HITSIC/utilities/rte_i2c.c \
../HITSIC/utilities/rte_softi2c.c \
../HITSIC/utilities/rte_spi.c \
../HITSIC/utilities/rte_uart.c 

OBJS += \
./HITSIC/utilities/app_menu.o \
./HITSIC/utilities/app_menu_button.o \
./HITSIC/utilities/app_menu_nvm.o \
./HITSIC/utilities/app_menu_type.o \
./HITSIC/utilities/drv_button.o \
./HITSIC/utilities/drv_disp_ssd1306.o \
./HITSIC/utilities/drv_ftfx_flash.o \
./HITSIC/utilities/drv_imu_invensense.o \
./HITSIC/utilities/lib_list.o \
./HITSIC/utilities/rte_i2c.o \
./HITSIC/utilities/rte_softi2c.o \
./HITSIC/utilities/rte_spi.o \
./HITSIC/utilities/rte_uart.o \
./HITSIC/utilities/sys_extint.o \
./HITSIC/utilities/sys_pitmgr.o \
./HITSIC/utilities/sys_uartmgr.o 

CPP_DEPS += \
./HITSIC/utilities/sys_extint.d \
./HITSIC/utilities/sys_pitmgr.d \
./HITSIC/utilities/sys_uartmgr.d 

C_DEPS += \
./HITSIC/utilities/app_menu.d \
./HITSIC/utilities/app_menu_button.d \
./HITSIC/utilities/app_menu_nvm.d \
./HITSIC/utilities/app_menu_type.d \
./HITSIC/utilities/drv_button.d \
./HITSIC/utilities/drv_disp_ssd1306.d \
./HITSIC/utilities/drv_ftfx_flash.d \
./HITSIC/utilities/drv_imu_invensense.d \
./HITSIC/utilities/lib_list.d \
./HITSIC/utilities/rte_i2c.d \
./HITSIC/utilities/rte_softi2c.d \
./HITSIC/utilities/rte_spi.d \
./HITSIC/utilities/rte_uart.d 


# Each subdirectory must supply rules for building sources it contributes
HITSIC/utilities/%.o: ../HITSIC/utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-c++ -std=c++17 -DCPU_MK66FX1M0VLQ18 -DCPU_MK66FX1M0VLQ18_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../board -I../source -I../source/module -I../HITSIC/utilities -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/inc -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/plugins/types -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/plugins/types/struct2json/inc -I../HITSIC/d_mk66f18 -I../HITSIC/d_mk66f18/legacy_drivers -I../HITSIC/d_mk66f18/extlib_port/EasyFlash-4.0.0/easyflash/port -I../ -I../amazon-freertos/freertos/portable -I../amazon-freertos/include -I../drivers -I../device -I../CMSIS -I../drivers/freertos -I../component/lists -I../component/serial_manager -I../utilities -I../component/uart -I../usb/include -I../osa -I../usb/phy -I../usb/device/class -I../usb/device/include -I../usb/device/source -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source/generated -I../usb/host/class -I../usb/host -I../fatfs -I../fatfs/fatfs_include -I../sdmmc/inc -I../sdmmc/port -I../component/serial_manager/usb_cdc_adapter -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

HITSIC/utilities/%.o: ../HITSIC/utilities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++17 -DCPU_MK66FX1M0VLQ18 -DCPU_MK66FX1M0VLQ18_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DSDK_DEBUGCONSOLE_UART -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I../board -I../source -I../source/module -I../HITSIC/utilities -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/inc -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/plugins/types -I../HITSIC/utilities/extlib/EasyFlash-4.0.0/easyflash/plugins/types/struct2json/inc -I../HITSIC/d_mk66f18 -I../HITSIC/d_mk66f18/legacy_drivers -I../HITSIC/d_mk66f18/extlib_port/EasyFlash-4.0.0/easyflash/port -I../ -I../amazon-freertos/freertos/portable -I../amazon-freertos/include -I../drivers -I../device -I../CMSIS -I../drivers/freertos -I../component/lists -I../component/serial_manager -I../utilities -I../component/uart -I../usb/include -I../osa -I../usb/phy -I../usb/device/class -I../usb/device/include -I../usb/device/source -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source/generated -I../usb/host/class -I../usb/host -I../fatfs -I../fatfs/fatfs_include -I../sdmmc/inc -I../sdmmc/port -I../component/serial_manager/usb_cdc_adapter -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -frtti -fexceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


