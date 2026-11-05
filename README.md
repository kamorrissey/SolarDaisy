# SolarDaisy

## Introduction
The SolarDaisy is an open-source solar garden light with animated LEDs.
The LEDs animate only in relative darkness.
All files needed to reproduce the device are included.

A 2V solar panel charges an AA 1.2V NiMH cell through a 1N5817 Schottky diode to limit current backflow from the cell to the panel.
The cell (possibly in addition to the panel) is boosted to 3.3V with a TPS613222 boost-buck regulator.
The regulator powers a PIC16F13115 microcontroller (MCU), which drives the LEDs of the light.


There are two groups of LEDs:
* a center color-cycling standard LED is on only when the MCU detects darkness
* a ring of six white, high-brightness, 3V standard LEDs
  are animated using three-wire [Charlieplexing](https://en.wikipedia.org/wiki/Charlieplexing),
  time-division multiplexing, and PWM (for brightness control)

There is a circular main PCB.
A breakaway portion is used in the charging section of the device.

The post and charging section, with a solar panel and battery holder, from a commercial solar garden walkway light are used to simplify manufacturing.
The 3d-printed parts are of modular design so that only one part need be redesigned to use a different walkway light.

## Project Layout
There are four primary folders:
  1. [artifacts](artifacts) - files from the original project deemed worth archiving
  1. [kicad](kicad) - KiCad projects for PCB designs
  1. [mplab](mplab) - MPLAB X projects for the firmware
  1. [solidworks](solidworks) - SOLIDWORKS CAD projects for 3d printable parts

## Building
Can be built with [MPLAB X IDE](https://www.microchip.com/mplab-x-ide)
or [MPLAB for VS Code](https://www.microchip.com/en-us/tools-resources/develop/mplab-tools-vs-code)
by opening the folder mplab/solar-charlie-16f13115.X in the desired MPLAB tool.

(Remainder to be provided)
