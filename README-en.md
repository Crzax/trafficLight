# Intelligent Traffic Light Design Based on 8051 Microcontroller

[![Keil 8051](https://img.shields.io/badge/Keil-8051-blue)](https://www.keil.com/download/product/)

[中文](README.md)

## Project Overview
This project is the second assignment for the 2023-2024 academic year Embedded Systems course at Wuhan University. It involves designing an intelligent traffic light control system based on the STC89C52RC microcontroller, simulating the operation of traffic signals at a real-world intersection. The functionalities include countdown display, red light delay, traffic light state settings, and additional features such as voice prompts, temperature detection, and fan control.

---

## Features

### Basic Features
1. **Traffic Light Control**:
   - Simulates traffic signal lights in four directions, including the transition of red, green, and yellow lights.
   - Default duration for each direction: red light for 16 seconds, green light for 13 seconds, yellow light for 3 seconds.

2. **Countdown Display**:
   - Uses dynamic digital displays to show the countdown time of the current signal light.
   - Provides a dynamic refresh mechanism to ensure smooth display without ghosting.

3. **Operator Settings**:
   - Supports setting countdown times via independent buttons or a matrix keyboard.
   - Custom mode allows real-time adjustment of red and green light durations.

### Additional Features (Bonus)
1. **Red Light Delay**:
   - An independent button extends the red light duration by 3 seconds in emergencies.
2. **Flashing Countdown**:
   - When the countdown is under 3 seconds, the signal lights and digital displays flash every 500ms to alert.
3. **Voice Prompt**:
   - A buzzer emits a warning tone when the green light countdown is under 6 seconds to alert pedestrians.
4. **Remote Control**:
   - Supports setting countdown times via an infrared remote control.
5. **Temperature Sensing and Fan Control**:
   - Uses a DS18B20 temperature sensor to detect temperature, automatically activating the fan for cooling when the temperature exceeds a set threshold.
