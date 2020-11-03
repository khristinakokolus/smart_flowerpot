# Smart Flowerpot project code for STM32

## Contributors
[Khrystyna Kokolus](https://github.com/khristinakokolus)

[Daryna Hnatenko](https://github.com/monberin)

[Zoryana Herman](https://github.com/zoriankaH)

## Current stage
Right now this project consists of a humidity sensor that collects the data and a display,
that shows collected humidity value represented in percentages.

## Compatibility
The code herein is compatible with 
* STM32F4 Discovery board (STM32F411E-DISCO)
* Nokia 5110 lcd display
* Capacitive Soil Moisture Sensor v1.2.

## General project layout
For now, the project is on its first stage, with only one sensor connected to the board. 

In the future, another one(light sensor) will be also implemented to help control the light levels.

For moisture control, a motor pump will be used to pump the water into the pot from a reservoir.

For water level control in the reservoir, we will use an ultrasonic wave detector.

A wi-fi module will be used for transmitting collected data from the flowerpot to the website.

## First presentation

https://docs.google.com/presentation/d/1q7wJt3yEb8WoOHoZEu2u7bHECblZe3X2M0yalXgQ2Qw/edit#slide=id.ga6ef44feec_2_16


## Cloning this Repository

```
git clone https://github.com/khristinakokolus/smart_flowerpot.git
```

