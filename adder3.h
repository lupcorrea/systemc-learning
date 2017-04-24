#ifndef _ADDER3_H_
#define _ADDER3_H_

#include "systemc.h"

SC_MODULE (adder3) {
    // IO
    sc_in<bool> A, B, Cin;
    sc_out<bool> S, Cout;
    
    void add() {
        S.write ((A.read() && B.read() && Cin.read()) || (A.read() xor B.read() xor Cin.read()));
        Cout.write ((A.read() && B.read()) || (A.read() && Cin.read()) || (B.read() && Cin.read()));
    }

    SC_CTOR (adder3) {
        SC_METHOD (add);
        sensitive << A << B << Cin;
    }     
};

#endif