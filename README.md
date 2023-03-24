# MSEC - Mortar Simultaneous Explosion Calulator
This simple 2D C++ application calculates the trajectories of mortar shells for a simultaneous explosion. Given the distance to the target, the application calculates the trajectory of each shell and determines the time, charge, and angle needed of the simultaneous explosion.

Its main application is a visual proof of the possibility of MSRI capabilities of shells for mortars.
# Installation
To install the application, clone the repository and use CMake to build the executable:

- Option 1: Using Binaries
If you do not wish to build the application yourself, pre-built binaries are available for download on the releases page. Simply download the appropriate binary for your system and run it.

- Option 2: Using cmake(not recommended for now because of the gtk dependencies and ninja, but cmakelists are provided)

# Usage
To use the application, run the executable and follow the prompts:


You will be prompted to choose type of the shell from the top list, and enter distance to the target, after you press the button the application will calculate the trajectories and display the time of the flight for shells to the same point with plausible time difference between the shots.

# Contributing
It is just fun home project of the one person, but if you are interested feel free to contact me.  

# License
This application is licensed under the MIT License. See the LICENSE file for more information.
