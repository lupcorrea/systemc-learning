#ifndef _STIM_H_
#define _STIM_H_

#include "systemc.h"
#include <stdlib.h>

#define RANGE 256

SC_MODULE (stim) {
    sc_out< sc_int<64> > A, B;
    sc_in<bool> Clock;
    
    void stimGen() {
        for (int i = 0; i < 10; i++) {
            A.write (rand() % RANGE);
            B.write (rand() % RANGE);
            wait();
        }
        
        sc_stop();
    }

    SC_CTOR (stim) {
        SC_THREAD (stimGen);
        sensitive << Clock.pos();
    }
};

#endif