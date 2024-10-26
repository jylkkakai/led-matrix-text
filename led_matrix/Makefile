################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#-include ../makefile.init

RM := rm -rf

ELFSIZE += \
led_matrix.elf.size \

LIBS := -Wl,--start-group,-lxil,-lgcc,-lc,--end-group

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
./src/lscript.ld 

C_SRCS += \
./src/helloworld.c \
./src/platform.c 

OBJS += \
./build/helloworld.o \
./build/platform.o 

C_DEPS += \
./build/helloworld.d \
./build/platform.d 

# Every subdirectory with source files must be described here
SUBDIRS := \
src \
build\

# All Target
all: pre-build main-build

# Main-build Target
main-build:  led_matrix.elf secondary-outputs

# Each subdirectory must supply rules for building sources it contributes
 build/%.o: ./src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	@mkdir -p $(@D)
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../led_matrix_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



# Tool invocations
led_matrix.elf: $(OBJS) src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 gcc linker'
	arm-none-eabi-gcc -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none -specs=Xilinx.spec -Wl,-T -Wl,src/lscript.ld -L../led_matrix_bsp/ps7_cortexa9_0/lib -o "led_matrix.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

led_matrix.elf.size: led_matrix.elf
	@echo 'Invoking: ARM v7 Print Size'
	arm-none-eabi-size led_matrix.elf  |tee "led_matrix.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) led_matrix.elf
	-@echo ' '

pre-build:
	-a9-linaro-pre-build-step
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

# -include ../makefile.targets
