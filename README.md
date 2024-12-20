# Project Zero
Project ***Zero*** is a personal project aimed at teaching myself CAD, CFD, electronic circuits, and flight software design. To accomplish this I am attempting to design and build something akin to a model rocket that is actively stabilized through use of aerodynamic fins.

I've decided that this project will have an iterative design approach, where I focus more on solving a single problem at a time, rather than spending a great deal of time trying to optimize every aspect of the design before implementing anything.
As a consequence, there will be inefficiencies. Code will need to be optimized. CAD models will need to be optimized. Circuits will need to be optimized.

The goal is to learn, and to have a physical (and electronic) record of my learning.

## Hardware
- Flight Computer: Arduino MKR Wifi 1010
- Sensors: MPU6050 IMU
- Actuators: SG90 Servos

## Flight Software
All of the flight software is developed in Visual Studio Code using the PlatformIO framework for building and uploading to the flight computer. Any software libraries not written by myself will be listed in the [platform.ini](https://github.com/codyauch/Project_Zero_FSW/blob/main/platformio.ini) file.

## CAD Models
Coming soon (hopefully)

## Iterations
||Main Objective:|status|
|-|-|-|
|1|Minimally complete model, active aerodynamic control|WIP|
