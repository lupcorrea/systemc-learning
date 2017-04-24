/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2014 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.accellera.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************
 
  simple_bus_test.h : The test bench.
 
  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
 
 *****************************************************************************/
 
/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
 
      Name, Affiliation, Date:
  Description of Modification:
 
 *****************************************************************************/

#ifndef __simple_bus_test_h
#define __simple_bus_test_h

#include <systemc.h>

#include "simple_bus_master_blocking.h"
#include "simple_bus_master_non_blocking.h"
#include "simple_bus_master_direct.h"
#include "simple_bus_slow_mem.h"
#include "simple_bus.h"
#include "simple_bus_fast_mem.h"
#include "simple_bus_arbiter.h"
#include "simple_bus_test.h"

#include "addresses.h"

SC_MODULE(simple_bus_test)
{
  // channels
  sc_clock C1;

  // module instances
  simple_bus_master_blocking     *master_w;
  simple_bus_slow_mem            *mem_input, *mem_map, *mem_output;
  simple_bus                     *bus;
  simple_bus_arbiter             *arbiter;

  // constructor
  SC_CTOR(simple_bus_test)
    : C1("C1")
  {
    // create instances
    master_w = new simple_bus_master_blocking("driver", 4, 0x00, false, 300, 0);
    mem_input = new simple_bus_slow_mem("input", INPUT_MEMORY_START, INPUT_MEMORY_END, 1);
    mem_map = new simple_bus_slow_mem ("map", MAP_MEMORY_START, MAP_MEMORY_END, 1);
    mem_output = new simple_bus_slow_mem ("output", OUTPUT_MEMORY_START, OUTPUT_MEMORY_END, 1);
    //bus = new simple_bus("bus",true); // verbose output
    bus = new simple_bus("bus");
    //arbiter = new simple_bus_arbiter("arbiter",true); // verbose output
    arbiter = new simple_bus_arbiter("arbiter");

    // connect instances
    bus->clock(C1);
    master_w->clock(C1);
    mem_input->clock(C1);
    mem_map->clock(C1);
    mem_output->clock(C1);
    master_w->bus_port(*bus);
    bus->arbiter_port(*arbiter);
    bus->slave_port(*mem_input);
    bus->slave_port(*mem_map);
    bus->slave_port(*mem_output);
  }

  // destructor
  ~simple_bus_test()
  {
    if (master_w) {delete master_w; master_w = 0;}
    if (mem_input) {delete mem_input; mem_input = 0;}
    if (mem_map) {delete mem_map; mem_map = 0;}
    if (mem_output) {delete mem_output; mem_output = 0;}
    if (bus) {delete bus; bus = 0;}
    if (arbiter) {delete arbiter; arbiter = 0;}
  }

}; // end class simple_bus_test

#endif
