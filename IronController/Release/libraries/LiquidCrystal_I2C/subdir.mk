################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/MAIN/Desktop/eclipseArduino/arduinoPlugin/libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.cpp 

O_SRCS += \
C:/Users/MAIN/Desktop/eclipseArduino/arduinoPlugin/libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.o 

LINK_OBJ += \
./libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.cpp.o 

CPP_DEPS += \
./libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.cpp.o: C:/Users/MAIN/Desktop/eclipseArduino/arduinoPlugin/libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\MAIN\Desktop\eclipseArduino\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Users\MAIN\Desktop\eclipseArduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.11\cores\arduino" -I"C:\Users\MAIN\Desktop\eclipseArduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.11\variants\eightanaloginputs" -I"C:\Users\MAIN\Desktop\eclipseArduino\arduinoPlugin\libraries\LiquidCrystal_I2C\1.1.2" -I"C:\Users\MAIN\Desktop\eclipseArduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.11\libraries\Wire" -I"C:\Users\MAIN\Desktop\eclipseArduino\arduinoPlugin\packages\arduino\hardware\avr\1.6.11\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


