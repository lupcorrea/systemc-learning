#ifndef _MULTI_H_
#define _MULTI_H_

#include "systemc.h"

SC_MODULE (multi) {
    // IO
    sc_in< sc_int<64> > A, B;
    sc_out< sc_int<64> > M;
    
    void mul() {
        M.write (A.read() * B.read());
    }

    SC_CTOR (multi) {
        SC_METHOD (mul);
        sensitive << A << B;
    }     
};

#endif