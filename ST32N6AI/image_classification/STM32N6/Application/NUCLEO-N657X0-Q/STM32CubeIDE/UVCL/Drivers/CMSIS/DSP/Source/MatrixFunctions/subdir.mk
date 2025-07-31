################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.c \
../Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.o \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.d \
./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/MatrixFunctions/%.o Drivers/CMSIS/DSP/Source/MatrixFunctions/%.su Drivers/CMSIS/DSP/Source/MatrixFunctions/%.cyclo: ../Drivers/CMSIS/DSP/Source/MatrixFunctions/%.c Drivers/CMSIS/DSP/Source/MatrixFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DSTM32N657xx -DLL_ATON_VERBOSE_ERR=1 -DSTM32N6570_NUCLEO_REV -DSCR_LIB_USE_UVCL -DSCR_LIB_USE_NONE -DUVC_LIB_USE_USBX -DUX_INCLUDE_USER_DEFINE_FILE -DUSBL_PACKET_PER_MICRO_FRAME=3 -DUX_STANDALONE -DUSE_FULL_ASSERT -DUSE_FULL_LL_DRIVER -DVECT_TAB_SRAM -DLL_ATON_DUMP_DEBUG_API -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DLL_ATON_RT_MODE=LL_ATON_RT_ASYNC -DLL_ATON_SW_FALLBACK -DLL_ATON_DBG_BUFFER_INFO_EXCLUDED=1 -c -I../../Inc -I../../../../Middlewares/AI_Runtime/Npu/ll_aton -I../../../../Middlewares/AI_Runtime/Npu/Devices/STM32N6XX -I../../../../STM32Cube_FW_N6/Drivers/STM32N6xx_HAL_Driver/Inc -I../../../../STM32Cube_FW_N6/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../../STM32Cube_FW_N6/Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../../STM32Cube_FW_N6/Drivers/CMSIS/Include -I../../../../STM32Cube_FW_N6/Drivers/BSP/Components/Common -I../../../../STM32Cube_FW_N6/Drivers/BSP/STM32N6xx_Nucleo -I../../../../Middlewares/Camera_Middleware/ISP_Library/isp/Inc -I../../../../Middlewares/Camera_Middleware/ISP_Library/evision/Inc -I../../../../Middlewares/AI_Runtime/Inc -I../../../../STM32Cube_FW_N6/Utilities/lcd -I../../../../Middlewares/Camera_Middleware -I../../../../STM32Cube_FW_N6/Drivers/BSP/Components/aps256xx -I../../../../Middlewares/Camera_Middleware/sensors -I../../../../Middlewares/Camera_Middleware/sensors/imx335 -I../../../../Middlewares/Camera_Middleware/sensors/vd6g -I../../../../Middlewares/Camera_Middleware/sensors/vd55g1 -I../../../../STM32Cube_FW_N6/Middlewares/ST/usbx/common/core/inc -I../../../../STM32Cube_FW_N6/Middlewares/ST/usbx/ports/generic/inc -I../../../../STM32Cube_FW_N6/Middlewares/ST/usbx/common/usbx_device_classes/inc -I../../../../STM32Cube_FW_N6/Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../../../Middlewares/screenl/Inc -I../../../../Middlewares/screenl/ili9341 -I../../../../Middlewares/screenl/uvcl/Inc -I../../../../Middlewares/screenl/uvcl/Src -I../../../../Middlewares/screenl/uvcl/Inc/usbx -I../../../../Middlewares/screenl/uvcl/Src/usbx -I"D:/PA2/Code/Projectwork2_Code/ST32N6AI/image_classification/STM32N6/Application/NUCLEO-N657X0-Q/STM32CubeIDE/NN_Sim" -I"D:/PA2/Code/Projectwork2_Code/ST32N6AI/image_classification/STM32N6/Application/NUCLEO-N657X0-Q/STM32CubeIDE/ATON_MatMul" -I../../../../STM32Cube_FW_N6/Drivers/CMSIS/DSP/Include -I../../../../STM32Cube_FW_N6/Drivers/CMSIS/DSP/PrivateInclude -Os -ffunction-sections -fdata-sections -Wall -flax-vector-conversions -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-MatrixFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-MatrixFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_add_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_init_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.d
	-$(RM) ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_f64.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_mult_q7.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_scale_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f16.su
	-$(RM) ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_f64.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_sub_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_f64.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_trans_q7.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.su ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.cyclo ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.d ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.o ./Drivers/CMSIS/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-MatrixFunctions

