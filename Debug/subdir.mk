################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../missingframes.c 

OBJS += \
./missingframes.o 

C_DEPS += \
./missingframes.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	/dls_sw/prod/tools/RHEL6-x86_64/hdf5/1-8-11/prefix/bin/h5cc -I/dls_sw/prod/tools/RHEL6-x86_64/hdf5/1-8-11/prefix/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


