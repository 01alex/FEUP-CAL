################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TP1-EasyPilot/src/Intersection.cpp \
../TP1-EasyPilot/src/connection.cpp \
../TP1-EasyPilot/src/dijkstra.cpp \
../TP1-EasyPilot/src/graphviewer.cpp \
../TP1-EasyPilot/src/main.cpp 

OBJS += \
./TP1-EasyPilot/src/Intersection.o \
./TP1-EasyPilot/src/connection.o \
./TP1-EasyPilot/src/dijkstra.o \
./TP1-EasyPilot/src/graphviewer.o \
./TP1-EasyPilot/src/main.o 

CPP_DEPS += \
./TP1-EasyPilot/src/Intersection.d \
./TP1-EasyPilot/src/connection.d \
./TP1-EasyPilot/src/dijkstra.d \
./TP1-EasyPilot/src/graphviewer.d \
./TP1-EasyPilot/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
TP1-EasyPilot/src/%.o: ../TP1-EasyPilot/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


