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

void simple_bus_master_blocking::generateMap() {
    simple_bus_status status;
    char buffer [104];
    
    buffer [0] = 'a';
    buffer [1] = 'b';
    buffer [2] = 'c';
    buffer [3] = 'd';
    buffer [4] = 'e';
    buffer [5] = 'f';
    buffer [6] = 'g';
    buffer [7] = 'h';
    buffer [8] = 'i';
    buffer [9] = 'j';
    buffer [10] = 'k';
    buffer [11] = 'l';
    buffer [12] = 'm';
    buffer [13] = 'n';
    buffer [14] = 'o';
    buffer [15] = 'p';
    buffer [16] = 'q';
    buffer [17] = 'r';
    buffer [18] = 's';
    buffer [19] = 't';
    buffer [20] = 'u';
    buffer [21] = 'v';
    buffer [22] = 'w';
    buffer [23] = 'x';
    buffer [24] = 'y';
    buffer [25] = 'z';
    
    int *ptr = (int *) buffer;
    status = bus_port->burst_write (m_unique_priority, ptr, MAP_MEMORY_START, 26, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n", 
        sc_time_stamp().to_string().c_str(), name(), MAP_MEMORY_START);
}

void simple_bus_master_blocking::generateRandomInput (int size) {
    simple_bus_status status;
    int buffer [size];
    
    for (int i = 0; i < size; i++) buffer [i] = rand() % 26 + 97;
    status = bus_port->burst_write (m_unique_priority, buffer, INPUT_MEMORY_START, size, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n", 
        sc_time_stamp().to_string().c_str(), name(), INPUT_MEMORY_START);
}

void simple_bus_master_blocking::check (int size) {
    char mapBuffer [26]; char outBuffer [size];
    int inBuffer [size]; int checkBuffer [size];
    simple_bus_status status;
    int *mapPtr = (int *) mapBuffer;
    int *outPtr = (int *) outBuffer;
    
    /* Read the input memory into the buffer */
    status = bus_port->burst_read (m_unique_priority, inBuffer, INPUT_MEMORY_START, size, m_lock);
    if (status == SIMPLE_BUS_ERROR)
	   sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                  sc_time_stamp().to_string().c_str(), name(), INPUT_MEMORY_START);
    
    /* Read the map memory into the buffer */
    status = bus_port->burst_read (m_unique_priority, mapPtr, MAP_MEMORY_START, 26, m_lock);
    if (status == SIMPLE_BUS_ERROR)
	   sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                  sc_time_stamp().to_string().c_str(), name(), MAP_MEMORY_START);
    
    /* Read the output memory into the buffer */
    status = bus_port->burst_read (m_unique_priority, outPtr, OUTPUT_MEMORY_START, size, m_lock);
    if (status == SIMPLE_BUS_ERROR)
	   sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                  sc_time_stamp().to_string().c_str(), name(), OUTPUT_MEMORY_START);
    
    /* Code output */
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 26; j++) {
            if (mapBuffer [j] == outBuffer [i]) {
                checkBuffer [i] = j + 97;
                break;
            }
        }
    }
    
    /* Display checking results */
    int victoryCount = 0;
    printf ("\n[Time]\t[Coded input]\t[Decoded message]\t[Check]\t[Diagnosis]\n");
    for (int i = 0; i < size; i++) {
        if (inBuffer[i] - checkBuffer [i] == 0) {
            victoryCount++;
            printf ("[%s]\t%d\t%c\t%d\tPASS\n", 
                sc_time_stamp().to_string().c_str(), inBuffer [i], outBuffer [i], checkBuffer [i]);
        } else printf ("[%s]\t%d\t%c\t%d\tFAIL\n", 
                sc_time_stamp().to_string().c_str(), inBuffer [i], outBuffer [i], checkBuffer [i]);
    }
    
    /* Final diagnosis */
    if (victoryCount != size) {
        printf("\n                                          ");
        printf("\n#########   #######   #########  ##       ");
        printf("\n##         ##     ##     ##      ##       ");
        printf("\n##         ##     ##     ##      ##       ");
        printf("\n######     #########     ##      ##       ");
        printf("\n##         ##     ##     ##      ##       ");
        printf("\n##         ##     ##     ##      ##       ");
        printf("\n##         ##     ##  #########   ########");
        printf("\n\n                                          \n");
    } else {
        printf("\n                                          ");
        printf("\n########    #######     ######     ###### ");
        printf("\n##     ##  ##     ##  ##     ##  ##     ##");
        printf("\n##     ##  ##     ##  ##         ##       ");
        printf("\n########   #########    ######     ###### ");
        printf("\n##         ##     ##         ##         ##");
        printf("\n##         ##     ##  ##     ##  ##     ##");
        printf("\n##         ##     ##    ######     ###### ");
        printf("\n                                          ");
        printf("\nSimulation completed without errors!\n");
      }
}

void simple_bus_master_blocking::decode (int size) {
    char mapBuffer [26]; char outBuffer [size];
    int inBuffer [size];
    simple_bus_status status;
    int *mapPtr = (int *) mapBuffer;
    int *outPtr = (int *) outBuffer;
    
    /* Read the input memory into the buffer */
    status = bus_port->burst_read (m_unique_priority, inBuffer, INPUT_MEMORY_START, size, m_lock);
    if (status == SIMPLE_BUS_ERROR)
	   sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                  sc_time_stamp().to_string().c_str(), name(), INPUT_MEMORY_START);
    
    /* Display in the screen data extracted from the memory *
    printf ("\n[%s] Input memory:\n", sc_time_stamp().to_string().c_str());
    for (int i = 0; i < size; i++) printf ("[%d] %d\n", i, inBuffer [i]);
    
    /* Read the map memory into the buffer */
    status = bus_port->burst_read (m_unique_priority, mapPtr, MAP_MEMORY_START, 26, m_lock);
    if (status == SIMPLE_BUS_ERROR)
	   sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                  sc_time_stamp().to_string().c_str(), name(), MAP_MEMORY_START);
    
    /* Display in the screen data extracted from the memory *
    printf ("\n[%s] Map memory:\n", sc_time_stamp().to_string().c_str());
    for (int i = 0; i < 26; i++) printf ("[%d] %c\n", i, mapBuffer [i]);
    
    /* Decode the input */
    for (int i = 0; i < size; i++) outBuffer [i] = mapBuffer [inBuffer [i] - 97];
    
    /* Write into output memory */
    status = bus_port->burst_write (m_unique_priority, outPtr, OUTPUT_MEMORY_START, size, m_lock);
    if (status == SIMPLE_BUS_ERROR) sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n", 
        sc_time_stamp().to_string().c_str(), name(), OUTPUT_MEMORY_START);
    
    /* Read the output memory into the buffer *
    status = bus_port->burst_read (m_unique_priority, outPtr, OUTPUT_MEMORY_START, size, m_lock);
    if (status == SIMPLE_BUS_ERROR)
	   sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                  sc_time_stamp().to_string().c_str(), name(), OUTPUT_MEMORY_START);
    
    /* Display in the screen data extracted from the memory *
    printf ("\n[%s] Output memory:\n", sc_time_stamp().to_string().c_str());
    for (int i = 0; i < 10; i++) printf ("[%d] %c\n", i, outBuffer [i]);
    /**/
    
    check (size);
}

void simple_bus_master_blocking::main_action() {
    const unsigned int dataSize = 10; // storage capacity/burst length in words
    
    switch (m_id) {
        case 0: generateMap ();
                generateRandomInput (dataSize);
                decode (dataSize);
                break;
     //   case 2: codeOutPut();
       //         check();
         //       break;
    }

  
}
