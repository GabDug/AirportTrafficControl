Compilation
===========

The project was developped with the IDE CLion and compiled with CMake.
We've added the CMakeList.txt with the sources.
The project compiled with the version sent.


Brief Description of the Realized Parts
=======================================

Time management is implemented.

Basic takeoff and landing are implemented.
Takeoffs will be on time when possible.
Users can add a plane to takeoff or landing, and see planes waiting for takeoff and landing.
They can't add a plane to takeoff in less than 5 minutes.

Log is implemented.

Crashes, blacklists, emergency landing, different fuel consumptions and reading from a test file are features not supported. 


Modifications after the presentation
====================================

The following features were implemented after the presentation:
- Landing
- Logging
- Can't add a plane to takeoff in less than 5 minutes
- User command to show takeoff or landing plane (the simulator showed the takeoff queue automatically)
