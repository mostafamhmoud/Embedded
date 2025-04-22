# FreeRTOS LED Control and RTC Management

## Description

This project is a FreeRTOS-based application that demonstrates LED control effects and real-time clock (RTC) management. The application allows users to configure the time and date, as well as control LED effects through a command-line interface.

## Features

- **LED Control**: Users can choose from different LED effects, including toggling all LEDs, turning on even or odd LEDs, and shifting LEDs left or right.
- **RTC Management**: The project allows users to configure and display the current time and date.
- **Task Management**: Implements multiple tasks to handle menu navigation, LED effects, RTC configuration, and command processing.

## Files

- `main.c`: The main entry point of the application, initializes peripherals and creates FreeRTOS tasks.
- `TaskHandlers.c`: Contains task implementations for menu handling, printing messages, RTC management, and LED effects.
- `RTC.c`: Manages RTC configuration and displays the current time and date.
- `LedEffect.c`: Implements various LED effects and control functions.
- `main.h`: Header file containing necessary includes and definitions.
