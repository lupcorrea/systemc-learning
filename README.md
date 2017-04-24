# 2 Bits Full Adder

## Brief Description and Credits

This is the source code used for developing a, like the title says, arithmetic unit that sums 2 bits number, with Carry-out. The experiment itself was based on an assignment for my H/S Design course, at the Federal University of Paraíba, in Brazil.

## How does it work?

#### Stimulus (stim.h)

The system is tested via a series of stimuli provoked by this module. Essentially, it generates signals to insert in the system, triggered by the positive edge of the clock.

#### Monitor (mon.h)
 In order to test the system, we should be able to check the input provided and its respective response. That's the role of this module.
 
#### 2 bit Adder (adder2.h)
It sums 2 bits together, producing an output and a carry-out (in this system considered a carry-in).

#### 3 bit Adder (adder3.h)
It sums 3 bits together, producing an output and a carry-out.

#### Full Adder (fullAdder.h)
This module brings all the system together. Notice that the carry-out produced by the 2 bit adder module is inserted as the third bit in the 3 bit adder module.

## To Do Hitlist
* Write report for the assignment.
* Modularize the code, C++ stylez.

## General Stats
* As in version 1.0, 2,5 hours were invested in total, including:
  * Research (I needed to remember how logic circuits works)
  * More Research (I needed to remember how SystemC works)
  * Coding
  * Debugging (In this case, only checking compilation errors)
  * Checking if every output was all right
* 2 new songs discovered on Spotify
