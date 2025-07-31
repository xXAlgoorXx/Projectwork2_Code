################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.c \
../Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.c \
../Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.c \
../Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.c \
../Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.c \
../Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.c \
../Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.c \
../Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.o \
./Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.o \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.o \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.o \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.o \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.o \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.o \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.d \
./Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.d \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.d \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.d \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.d \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.d \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.d \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/CommonTables/%.o Drivers/CMSIS/DSP/Source/CommonTables/%.su Drivers/CMSIS/DSP/Source/CommonTables/%.cyclo: ../Drivers/CMSIS/DSP/Source/CommonTables/%.c Drivers/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DSTM32N657xx -DLL_ATON_VERBOSE_ERR=1 -DSTM32N6570_NUCLEO_REV -DSCR_LIB_USE_UVCL -DSCR_LIB_USE_NONE -DUVC_LIB_USE_USBX -DUX_INCLUDE_USER_DEFINE_FILE -DUSBL_PACKET_PER_MICRO_FRAME=3 -DUX_STANDALONE -DUSE_FULL_ASSERT -DUSE_FULL_LL_DRIVER -DVECT_TAB_SRAM -DLL_ATON_DUMP_DEBUG_API -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_RT_MODE=LL_ATON_RT_ASYNC -DLL_ATON_SW_FALLBACK -DLL_ATON_DBG_BUFFER_INFO_EXCLUDED=1 -c -I../../Inc -I../../../../Middlewares/AI_Runtime/Npu/ll_aton -I../../../../Middlewares/AI_Runtime/Npu/Devices/STM32N6XX -I../../../../STM32Cube_FW_N6/Drivers/STM32N6xx_HAL_Driver/Inc -I../../../../STM32Cube_FW_N6/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../../STM32Cube_FW_N6/Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../../STM32Cube_FW_N6/Drivers/CMSIS/Include -I../../../../STM32Cube_FW_N6/Drivers/BSP/Components/Common -I../../../../STM32Cube_FW_N6/Drivers/BSP/STM32N6xx_Nucleo -I../../../../Middlewares/Camera_Middleware/ISP_Library/isp/Inc -I../../../../Middlewares/Camera_Middleware/ISP_Library/evision/Inc -I../../../../Middlewares/AI_Runtime/Inc -I../../../../STM32Cube_FW_N6/Utilities/lcd -I../../../../Middlewares/Camera_Middleware -I../../../../STM32Cube_FW_N6/Drivers/BSP/Components/aps256xx -I../../../../Middlewares/Camera_Middleware/sensors -I../../../../Middlewares/Camera_Middleware/sensors/imx335 -I../../../../Middlewares/Camera_Middleware/sensors/vd6g -I../../../../Middlewares/Camera_Middleware/sensors/vd55g1 -I../../../../STM32Cube_FW_N6/Middlewares/ST/usbx/common/core/inc -I../../../../STM32Cube_FW_N6/Middlewares/ST/usbx/ports/generic/inc -I../../../../STM32Cube_FW_N6/Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../../../STM32Cube_FW_N6/Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../../../Middlewares/screenl/Inc -I../../../../Middlewares/screenl/ili9341 -I../../../../Middlewares/screenl/uvcl/Inc -I../../../../Middlewares/screenl/uvcl/Src -I../../../../Middlewares/screenl/uvcl/Inc/usbx -I../../../../Middlewares/screenl/uvcl/Src/usbx -I"D:/PA2/Code/Projectwork2_Code/ST32N6AI/image_classification/STM32N6/Application/NUCLEO-N657X0-Q/STM32CubeIDE/NN_Sim" -I"D:/PA2/Code/Projectwork2_Code/ST32N6AI/image_classification/STM32N6/Application/NUCLEO-N657X0-Q/STM32CubeIDE/ATON_MatMul" -I../../../../STM32Cube_FW_N6/Drivers/CMSIS/DSP/Include -I../../../../STM32Cube_FW_N6/Drivers/CMSIS/DSP/PrivateInclude -Os -ffunction-sections -fdata-sections -Wall -flax-vector-conversions -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables

clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables:
	-$(RM) ./Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.cyclo ./Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.d ./Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.o ./Drivers/CMSIS/DSP/Source/CommonTables/CommonTables.su ./Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.cyclo ./Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.d ./Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.o ./Drivers/CMSIS/DSP/Source/CommonTables/CommonTablesF16.su ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.cyclo ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.d ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.o ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.su ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.cyclo ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.d ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.o ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables_f16.su ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.cyclo ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.d ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.o ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.su ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.cyclo ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.d ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.o ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs_f16.su ./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.cyclo ./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.d ./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.o ./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables.su ./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.cyclo ./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.d ./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.o ./Drivers/CMSIS/DSP/Source/CommonTables/arm_mve_tables_f16.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables

