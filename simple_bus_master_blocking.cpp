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
 
  simple_bus_master_blocking.cpp : The master using the blocking BUS interface.
 
  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11
 
 *****************************************************************************/
 
/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
 
      Name, Affiliation, Date:
  Description of Modification:
 
 *****************************************************************************/

#include "simple_bus_master_blocking.h"
#include <stdlib.h>

void simple_bus_master_blocking::main_action() {
    const unsigned int dataSize = 10; // storage capacity/burst length in words
    int buffer [dataSize];
    simple_bus_status status;
    
    /******************** Initial filling ********************/
    
    /* Fill the buffer with 1000 random integers */
    for (int i = 0; i < dataSize; i++) buffer [i] = rand() % 10;
    
    /* Display in the screen buffer */
    printf ("\n[%s] Buffer before writing origin memory:\n", sc_time_stamp().to_string().c_str());
    for (int i = 0; i < dataSize; i++) printf ("[%d] %d\n", i, buffer [i]);
    
    /* Write the buffer into the origin memory */
    status = bus_port->burst_write (m_unique_priority, buffer, m_address, dataSize, m_lock);
    if (status == SIMPLE_BUS_ERROR)
        sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n", 
                   sc_time_stamp().to_string().c_str(), name(), m_address);

    /* Clean the buffer just to make sure transference won't be dirty. */
    for (int i = 0; i < dataSize; i++) buffer [i] = 0;
    
    /* Display in the screen buffer */
    printf ("\n[%s] Buffer after writing origin memory:\n", sc_time_stamp().to_string().c_str());
    for (int i = 0; i < dataSize; i++) printf ("[%d] %d\n", i, buffer [i]);
    
    /******************** Origin memory reading ********************/
    
    /* Read the origin memory into the buffer */
    status = bus_port->burst_read (m_unique_priority, buffer, m_address, dataSize, m_lock);
    if (status == SIMPLE_BUS_ERROR)
	   sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                  sc_time_stamp().to_string().c_str(), name(), m_address);
    
    /* Display in the screen data extracted from the memory */
    printf ("\n[%s] Origin memory:\n", sc_time_stamp().to_string().c_str());
    for (int i = 0; i < dataSize; i++) printf ("[%d] %d\n", i, buffer [i]);
    
    /******************** Destination memory writing ********************/
    
    /* Write the buffer into the destination memory */
    status = bus_port->burst_write (m_unique_priority, buffer, 0x3e84, dataSize, m_lock);
    if (status == SIMPLE_BUS_ERROR)
        sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n", 
                   sc_time_stamp().to_string().c_str(), name(), 0x3e84);
    
    /* Clean the buffer just to make sure transference won't be dirty. */
    for (int i = 0; i < dataSize; i++) buffer [i] = 0;
    
    /* Display in the screen buffer */
    printf ("\n[%s] Buffer before reading destination memory:\n", sc_time_stamp().to_string().c_str());
    for (int i = 0; i < dataSize; i++) printf ("[%d] %d\n", i, buffer [i]);
    
    /* Read the destination memory into the buffer */
    status = bus_port->burst_read (m_unique_priority, buffer, 0x3e84, dataSize, m_lock);
    if (status == SIMPLE_BUS_ERROR)
	   sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                  sc_time_stamp().to_string().c_str(), name(), 0x3e84);
    
    /* Display in the screen data extracted from the memory */
    printf ("\n[%s] Destination memory:\n", sc_time_stamp().to_string().c_str());
    for (int i = 0; i < dataSize; i++) printf ("[%d] %d\n", i, buffer [i]);
  
}
