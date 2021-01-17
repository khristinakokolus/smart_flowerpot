# Smart Flowerpot project code for STM32

## Contributors
[Khrystyna Kokolus](https://github.com/khristinakokolus)

[Daryna Hnatenko](https://github.com/monberin)

[Zoryana Herman](https://github.com/zoriankaH)

## Current stage
Right now this project consists of a humidity sensor and light sensor that collect the data and a display,
that shows collected humidity value represented in percentages. Also, using pump and relay it can
water the flower. In addition to this, the project has light system that consists of two light emitting diodes.

## Compatibility
The code herein is compatible with 
* STM32F4 Discovery board (STM32F411E-DISCO)
* Nokia 5110 lcd display
* Capacitive Soil Moisture Sensor v1.2.
* Photoresistor
* Water pump
* Tongle relay
* Two light emitting diodes
* uln2003
* Power supply
* Range-finder HC-SRO4


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

## First presentation

https://docs.google.com/presentation/d/1q7wJt3yEb8WoOHoZEu2u7bHECblZe3X2M0yalXgQ2Qw/edit#slide=id.ga6ef44feec_2_16

## Second presentation

https://docs.google.com/presentation/d/1_il1YektkvcEoaa66g5Y_mPef7qdFaaRjCFx2uGNQVo/edit#slide=id.p

## Cloning this Repository

```
git clone https://github.com/khristinakokolus/smart_flowerpot.git
```

