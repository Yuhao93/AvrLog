AvrLog
======

Uses 3 pins to send messages between a raspberry pi and an atmega 32.

One pin sends messages from the raspberry pi to the microcontroller (raspberry pi is output, microcontroller is input)
while two pins send data from the microcontroller to the raspberry pi (raspberry ip is input, microcontroller is output)

The raspberry pi uses the wiringPi library to for gpio communication.
