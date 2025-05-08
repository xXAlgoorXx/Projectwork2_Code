################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/lukasschoepf/Documents/ProjectWork_2/MatMulforMCU/MatmulCMSISDSP/src/matmulcmsis.c 

OBJS += \
./srcCMSIS/matmulcmsis.o 

C_DEPS += \
./srcCMSIS/matmulcmsis.d 


# Each subdirectory must supply rules for building sources it contributes
srcCMSIS/matmulcmsis.o: /home/lukasschoepf/Documents/ProjectWork_2/MatMulforMCU/MatmulCMSISDSP/src/matmulcmsis.c srcCMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I"/home/lukasschoepf/Documents/ProjectWork_2/MatMulforMCU/MatmulCMSISDSP/inc" -I"/home/lukasschoepf/STM32CubeIDE/V18/G4_Matmul/Drivers/CMSIS_DSP/Include" -I"/home/lukasschoepf/STM32CubeIDE/V18/G4_Matmul/Drivers/CMSIS_DSP/PrivateInclude" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32G4xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I/MatMulforMCU/MatmulBasic -I"/home/lukasschoepf/Documents/ProjectWork_2/MatMulforMCU/MatmulBasic/inc" -I/MatMulforMCU/MatmulCMSISDSP/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-srcCMSIS

clean-srcCMSIS:
	-$(RM) ./srcCMSIS/matmulcmsis.cyclo ./srcCMSIS/matmulcmsis.d ./srcCMSIS/matmulcmsis.o ./srcCMSIS/matmulcmsis.su

.PHONY: clean-srcCMSIS

