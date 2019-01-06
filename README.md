PidControlTemplate
============

Simple PID controllers template for general control problems solving, it contains a common interface
and user can select between numerical or 2p2z alghoritm, this template are intented to be used with
32bit microcontrollers/processors preferably with FPU.

# Features:
- Fast, execute the complete PID loop plus history updtade in <200ns @ 80MHz (ARM CORTEX M4F)
- Simple, create a pid, tune on the fly, and use it, only 3 apis;
- Common interface, user selectable algorithm;

# Example
 Inside of example folder you will find a code which can be used as starting point of your 
 PID control project, it is buildable and you need only to modify /add specific chip 
 code to get it running. If you are in linux a simple makefile was provided to 
 build it and get the things running just type:

 ```
 $ make all
 ```
- and a executable ready to use will be provided.

# Support:
 - If you want some help with this work give a star and contact me: ryukokki.felipe@gmail.com
