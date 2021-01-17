# Smart Flowerpot project code for STM32

Welcome to the Smart Flowerpot project!

## Contributors
[Khrystyna Kokolus](https://github.com/khristinakokolus)

[Daryna Hnatenko](https://github.com/monberin)

[Zoryana Herman](https://github.com/zoriankaH)

## Description
Smart Flowerpot embodies assistance in taking care of plants. This device can solve such problems as:

* lightning the plant if there is need;
* measurement of soil moisture;
* watering the plant if there is need;

## Current stage
Right now this project consists of a humidity sensor, light sensor and a range finder that collect the data, a display,
that shows collected humidity value represented in percentages, the light and water levels. 

Also, it waters the plant by using a pump when the humidity levels are too low. 

The light system of the project consists of two light emitting diodes, that are turned on/off corresponding to the light level of the environment.

The safety system consists of a relay module, positioned between the power supply and the main board, a current sensor, that measures if the current is present to the water pump, and a board that controls both. 

If the current is present for too long, the safety system shuts off the entire main board as to prevent leaks. 

## Compatibility and System Parts
The code herein is compatible with 
* STM32F4 Discovery board (STM32F411E-DISCO)
* Nokia 5110 lcd display
* Capacitive Soil Moisture Sensor v1.2.
* Photoresistor
* Water pump
* Tongle relay (x2)
* Two light emitting diodes
* uln2003
* Power supply
* Range-finder HC-SRO4
* ACS712 Current Sensor Module


## General project layout

---------------------------------FIRST STAGE-------------------------------------------

First stage - with only one sensor connected to the board - capacitive soil moisture with a display. 

---------------------------------SECOND STAGE-------------------------------------------

Another one(light sensor) is also implemented to help control the light levels using two LEDs.

For moisture control, a motor pump is used to pump the water into the pot from a reservoir.

For water level control in the reservoir, we use an ultrasonic wave detector.

---------------------------------THIRD STAGE-------------------------------------------

The system is powered from a power supply and is independent.

A safety system is integrated to protect the flowerpot from the malfunctioning.

## Device prototype


## First presentation

https://docs.google.com/presentation/d/1q7wJt3yEb8WoOHoZEu2u7bHECblZe3X2M0yalXgQ2Qw/edit#slide=id.ga6ef44feec_2_16

## Second presentation

https://docs.google.com/presentation/d/1_il1YektkvcEoaa66g5Y_mPef7qdFaaRjCFx2uGNQVo/edit#slide=id.p

## Third presentation

https://docs.google.com/presentation/d/18os2GDgEw6rZ8zcXJJtTPWbyIMYb-L4hANoLNsaLuLs/edit#slide=id.p

## Cloning this Repository

```
git clone https://github.com/khristinakokolus/smart_flowerpot.git
```

