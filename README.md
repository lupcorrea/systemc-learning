# Arithmetic Unit

## Brief Description and Credits

This is the source code used for developing an arithmetic unit that sums two integer numbers and multiply one of them by the sum output. This is done using solely SystemC data types and structures. The experiment itself was based on an assignment for my H/S Design course, at the Federal University of Paraíba, in Brazil.

## How does it work?

#### Stimulus (stim.h)

The system is tested via a series of stimuli provoked by this module. Essentially, it generates signals to insert in the system, triggered by the positive edge of the clock. Please notice that the machine is configured to generate random 8-bit stimuli, as defined by the constant RANGE. If you wish to change that condition, change this constant's value. Mind, though, that 32 or 64-bit might provoke an overflow in the system as the two numbers follow the pipeline, since the channels currently only support up to 64 bits. 

#### Monitor (mon.h)
 In order to test the system, we should be able to check the input provided and its respective response. That's the role of this module.
 
#### Adder (adder.h)
It sums 2 integer numbers (sc_int) together, producing an integer output.

#### Multiplier (multi.h)
This module multiplies 2 integer numbers (sc_int) together, producing an integer output.

## To Do Hitlist
* Write report for the assignment.
* Modularize the code, C++ stylez.

## General Stats
* As in version 0.2, 40 minutes were invested in total, including:
  * Research as to find out how SystemC structures could be used.
  * Coding
  * Debugging, to check compilation errors, and to figure out how to use SystemC structures at the communication channels.
  * Checking if every output was all right
  * Observing, from the monitor output, that the system outputs only woke up from the second cycle of execution, computing the second cycle of inputs. That means that the input variation that is supposed to wake up the outputs comes from the previous cycle, but once they are awakened, they will respond to the current cycle's inputs.
