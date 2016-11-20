################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CPPGraphAlgorithms/graph.cpp \
../CPPGraphAlgorithms/graphalgorithm.cpp \
../CPPGraphAlgorithms/testgraph.cpp \
../CPPGraphAlgorithms/unweightedgraph.cpp \
../CPPGraphAlgorithms/weightedgraph.cpp 

OBJS += \
./CPPGraphAlgorithms/graph.o \
./CPPGraphAlgorithms/graphalgorithm.o \
./CPPGraphAlgorithms/testgraph.o \
./CPPGraphAlgorithms/unweightedgraph.o \
./CPPGraphAlgorithms/weightedgraph.o 

CPP_DEPS += \
./CPPGraphAlgorithms/graph.d \
./CPPGraphAlgorithms/graphalgorithm.d \
./CPPGraphAlgorithms/testgraph.d \
./CPPGraphAlgorithms/unweightedgraph.d \
./CPPGraphAlgorithms/weightedgraph.d 


# Each subdirectory must supply rules for building sources it contributes
CPPGraphAlgorithms/%.o: ../CPPGraphAlgorithms/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


