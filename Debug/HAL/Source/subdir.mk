################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Source/HAL_Clock.c \
../HAL/Source/HAL_Flash.c \
../HAL/Source/HAL_GPIO.c \
../HAL/Source/HAL_LPUART.c \
../HAL/Source/HAL_NVIC.c \
../HAL/Source/HAL_systick.c 

C_DEPS += \
./HAL/Source/HAL_Clock.d \
./HAL/Source/HAL_Flash.d \
./HAL/Source/HAL_GPIO.d \
./HAL/Source/HAL_LPUART.d \
./HAL/Source/HAL_NVIC.d \
./HAL/Source/HAL_systick.d 

OBJS += \
./HAL/Source/HAL_Clock.o \
./HAL/Source/HAL_Flash.o \
./HAL/Source/HAL_GPIO.o \
./HAL/Source/HAL_LPUART.o \
./HAL/Source/HAL_NVIC.o \
./HAL/Source/HAL_systick.o 


# Each subdirectory must supply rules for building sources it contributes
HAL/Source/%.o: ../HAL/Source/%.c HAL/Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Bootloader_Application\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\User_Application\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\SregLib" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Queue" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Driver\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\HAL\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\device" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-HAL-2f-Source

clean-HAL-2f-Source:
	-$(RM) ./HAL/Source/HAL_Clock.d ./HAL/Source/HAL_Clock.o ./HAL/Source/HAL_Flash.d ./HAL/Source/HAL_Flash.o ./HAL/Source/HAL_GPIO.d ./HAL/Source/HAL_GPIO.o ./HAL/Source/HAL_LPUART.d ./HAL/Source/HAL_LPUART.o ./HAL/Source/HAL_NVIC.d ./HAL/Source/HAL_NVIC.o ./HAL/Source/HAL_systick.d ./HAL/Source/HAL_systick.o

.PHONY: clean-HAL-2f-Source

