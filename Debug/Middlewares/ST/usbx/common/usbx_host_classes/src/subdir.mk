################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_activate.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_capabilities_get.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_command.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_configure.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_deactivate.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_endpoints_get.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_entry.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_ioctl.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_read.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_callback.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_start.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_stop.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_transfer_request_completed.c \
../Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_write.c 

OBJS += \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_activate.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_capabilities_get.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_command.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_configure.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_deactivate.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_endpoints_get.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_entry.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_ioctl.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_read.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_callback.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_start.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_stop.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_transfer_request_completed.o \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_write.o 

C_DEPS += \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_activate.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_capabilities_get.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_command.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_configure.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_deactivate.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_endpoints_get.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_entry.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_ioctl.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_read.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_callback.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_start.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_stop.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_transfer_request_completed.d \
./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_write.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/usbx/common/usbx_host_classes/src/%.o Middlewares/ST/usbx/common/usbx_host_classes/src/%.su Middlewares/ST/usbx/common/usbx_host_classes/src/%.cyclo: ../Middlewares/ST/usbx/common/usbx_host_classes/src/%.c Middlewares/ST/usbx/common/usbx_host_classes/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -DTX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../AZURE_RTOS/App -I../USBX/App -I../USBX/Target -I../Middlewares/ST/usbx/common/usbx_host_classes/inc/ -I../Middlewares/ST/usbx/common/core/inc/ -I../Middlewares/ST/usbx/ports/generic/inc/ -I../Middlewares/ST/usbx/common/usbx_stm32_host_controllers/ -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-usbx-2f-common-2f-usbx_host_classes-2f-src

clean-Middlewares-2f-ST-2f-usbx-2f-common-2f-usbx_host_classes-2f-src:
	-$(RM) ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_activate.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_activate.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_activate.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_activate.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_capabilities_get.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_capabilities_get.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_capabilities_get.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_capabilities_get.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_command.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_command.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_command.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_command.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_configure.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_configure.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_configure.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_configure.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_deactivate.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_deactivate.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_deactivate.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_deactivate.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_endpoints_get.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_endpoints_get.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_endpoints_get.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_endpoints_get.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_entry.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_entry.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_entry.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_entry.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_ioctl.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_ioctl.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_ioctl.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_ioctl.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_read.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_read.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_read.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_read.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_callback.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_callback.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_callback.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_callback.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_start.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_start.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_start.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_start.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_stop.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_stop.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_stop.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_reception_stop.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_transfer_request_completed.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_transfer_request_completed.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_transfer_request_completed.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_transfer_request_completed.su ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_write.cyclo ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_write.d ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_write.o ./Middlewares/ST/usbx/common/usbx_host_classes/src/ux_host_class_cdc_acm_write.su

.PHONY: clean-Middlewares-2f-ST-2f-usbx-2f-common-2f-usbx_host_classes-2f-src

