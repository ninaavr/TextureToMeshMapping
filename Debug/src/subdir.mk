################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Free_matrix_loader.cpp \
../src/Matrix_calculator.cpp \
../src/Matrix_loader.cpp \
../src/Pinned_matrix_loader.cpp \
../src/main.cpp 

OBJS += \
./src/Free_matrix_loader.o \
./src/Matrix_calculator.o \
./src/Matrix_loader.o \
./src/Pinned_matrix_loader.o \
./src/main.o 

CPP_DEPS += \
./src/Free_matrix_loader.d \
./src/Matrix_calculator.d \
./src/Matrix_loader.d \
./src/Pinned_matrix_loader.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


