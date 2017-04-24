#ifndef _ADDER2_H_
#define _ADDER2_H_

#include "systemc.h"

SC_MODULE (adder2) {
    // IO
    sc_in<bool> A, B;
    sc_out<bool> S, Cout;
    
    void add() {
        S.write (A.read() xor B.read());
        Cout.write (A.read() && B.read());
    }

    SC_CTOR (adder2) {
        SC_METHOD (add);
        sensitive << A << B;
    }     
};

#endif