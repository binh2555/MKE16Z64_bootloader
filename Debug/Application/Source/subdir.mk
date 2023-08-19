################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Source/main.c 

C_DEPS += \
./Application/Source/main.d 

OBJS += \
./Application/Source/main.o 


# Each subdirectory must supply rules for building sources it contributes
Application/Source/%.o: ../Application/Source/%.c Application/Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\User_Application\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\SregLib" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Queue" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Application\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\Driver\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\HAL\Include" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\device" -I"D:\fsoft\MCU\S32studio_ide\ass5\ASS5\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Application-2f-Source

clean-Application-2f-Source:
	-$(RM) ./Application/Source/main.d ./Application/Source/main.o

.PHONY: clean-Application-2f-Source

