################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/nes/InfoNES.c \
../src/nes/InfoNES_Mapper.c \
../src/nes/InfoNES_pAPU.c \
../src/nes/InfoNES_system.c \
../src/nes/K6502.c \
../src/nes/rom.c 

OBJS += \
./src/nes/InfoNES.o \
./src/nes/InfoNES_Mapper.o \
./src/nes/InfoNES_pAPU.o \
./src/nes/InfoNES_system.o \
./src/nes/K6502.o \
./src/nes/rom.o 

C_DEPS += \
./src/nes/InfoNES.d \
./src/nes/InfoNES_Mapper.d \
./src/nes/InfoNES_pAPU.d \
./src/nes/InfoNES_system.d \
./src/nes/K6502.d \
./src/nes/rom.d 


# Each subdirectory must supply rules for building sources it contributes
src/nes/%.o: ../src/nes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -std=gnu11 -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


