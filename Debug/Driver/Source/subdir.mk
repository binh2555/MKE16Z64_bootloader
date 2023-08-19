################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Source/Driver_Clock.c \
../Driver/Source/Driver_Flash.c \
../Driver/Source/Driver_GPIO.c \
../Driver/Source/Driver_LPUART.c \
../Driver/Source/Driver_NVIC.c \
../Driver/Source/Driver_systick.c 

C_DEPS += \
./Driver/Source/Driver_Clock.d \
./Driver/Source/Driver_Flash.d \
./Driver/Source/Driver_GPIO.d \
./Driver/Source/Driver_LPUART.d \
./Driver/Source/Driver_NVIC.d \
./Driver/Source/Driver_systick.d 

OBJS += \
./Driver/Source/Driver_Clock.o \
./Driver/Source/Driver_Flash.o \
./Driver/Source/Driver_GPIO.o \
./Driver/Source/Driver_LPUART.o \
./Driver/Source/Driver_NVIC.o \
./Driver/Source/Driver_systick.o 


# Each subdirectory must supply rules for building sources it contributes
Driver/Source/%.o: ../Driver/Source/%.c Driver/Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Bootloader_Application\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\User_Application\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\SregLib" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Queue" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Driver\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\HAL\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\device" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Driver-2f-Source

clean-Driver-2f-Source:
	-$(RM) ./Driver/Source/Driver_Clock.d ./Driver/Source/Driver_Clock.o ./Driver/Source/Driver_Flash.d ./Driver/Source/Driver_Flash.o ./Driver/Source/Driver_GPIO.d ./Driver/Source/Driver_GPIO.o ./Driver/Source/Driver_LPUART.d ./Driver/Source/Driver_LPUART.o ./Driver/Source/Driver_NVIC.d ./Driver/Source/Driver_NVIC.o ./Driver/Source/Driver_systick.d ./Driver/Source/Driver_systick.o

.PHONY: clean-Driver-2f-Source

