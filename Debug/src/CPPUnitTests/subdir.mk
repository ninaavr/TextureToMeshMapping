################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CPPUnitTests/CalculationsTestSuite.cpp \
../src/CPPUnitTests/LoadingTestSuite.cpp \
../src/CPPUnitTests/SeamPinnedTestSuite.cpp 

OBJS += \
./src/CPPUnitTests/CalculationsTestSuite.o \
./src/CPPUnitTests/LoadingTestSuite.o \
./src/CPPUnitTests/SeamPinnedTestSuite.o 

CPP_DEPS += \
./src/CPPUnitTests/CalculationsTestSuite.d \
./src/CPPUnitTests/LoadingTestSuite.d \
./src/CPPUnitTests/SeamPinnedTestSuite.d 


# Each subdirectory must supply rules for building sources it contributes
src/CPPUnitTests/%.o: ../src/CPPUnitTests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


