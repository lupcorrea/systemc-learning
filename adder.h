#ifndef _ADDER_H_
#define _ADDER_H_

#include "systemc.h"

SC_MODULE (adder) {
    // IO
    sc_in< sc_int<64> > A, B;
    sc_out< sc_int<64> > S;
    
    void add() {
        S.write (A.read() + B.read());
    }

    SC_CTOR (adder) {
        SC_METHOD (add);
        sensitive << A << B;
    }     
};

#endif