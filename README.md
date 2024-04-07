# Introduction
This is a first draft of a custom homing module for **cia402** compatible ethercat drives.
It is inspired by @marcoreps work for [Leadshine el8 drives] (https://github.com/marcoreps/linuxcnc_leadshine_EL8)
And Dominc Brauns [cia402.comp] (https://github.com/dbraun1981/hal-cia402)
Many thanks to Dewey Garrett for the homecomp.comp method for developing custom homing modules using halcompile.
The initial version of homecomp required hundreds of unnecessary lines of code to be copied boiler plate from homing.c
Dewey subsequently vastly simplified the homemod structure so this was no longer required as many procedures are now by default templated.
# Why a Custom Homing Component for cia402 drives?
Homing in linuxcnc is managed in the source file [homing.c](https://github.com/LinuxCNC/linuxcnc/blob/master/src/emc/motion/homing.c)
There are many steps that are required for Linuxcnc to home a drive which are stepped through in sequential order via a state machine in homing.c
With a **cia402** ethercat drive, homing can be done internally with the drive which is foreign to linuxcnc because it sees motion it did not command.
All that needs to be done is for linuxcnc to tell the drive to home and wait for it to complete the process and then have the drive tell linuxcnc when its done.
But because motion occurs outside of linuxcnc, while the drive is homing following errors will occur. The solution to this is set pos_fb = pos_cmd while homing.
A custom homing module bypasses the unnecessary homing states and updates the linuxcnc of the position feedback while there is external motion.
## Whats wrong with cia402.comp?
This earlier work by Dominc was designed to home  cia402 drives was based on using home to index on a drive with an absolute encoder and not for the many possible homing cia402 methods 
using torque or external homing switches attached to the drive itself. Prior to the homecomp method, to get external homing to work required modification of homing.c and rebuilding linuxnc.
# How does it work?
This component requires an understanding of linuxcnc internals. It is complicated because it deals with all joints at one time. First, lets decide on the pins we need which are added to the joints
   - **joint.n.request_cia402_homing**
   - **joint.n.is_cia402_homing**
   - **joint.n.cia402_homing_finished**

To manage these pins and the cia402 external homing process we require:
1. A structure to hold the pin data for each joint
2. A procedure to create the pins
3. A procedure to read the pin values into the structure when the homecomp is called
4. A procedure to write back the pin values when exiting the homecomp for that joint
5. A state machine that sets the program flow.

Hopefully, this background will help users understand how this component works.

# Building and Installing the custom cia402 homing component
This component can be built using halcompile but it requires the source code of **homing.c** to exist on your computer. The location of this file must be set in the source code.
```
#define HOMING_BASE home/rod/linuxcnc-dev/src/emc/motion/homing.c
```
Install linuxcnc from its repositories
```
git clone https://github.com/LinuxCNC/linuxcnc.git linuxcnc-dev
```
