#ifndef _ADDER4_H_
#define _ADDER4_H_

#include "systemc.h"
#include "adder2.h"
#include "adder3.h"

SC_MODULE (fullAdder) {
    // IO
    sc_in<bool> A0, A1, B0, B1;
    sc_out<bool> S0, S1, Cout;
    
    // Communication between adders
    sc_signal<bool> Cin;
    
    // Adders
    adder2 add2;
    adder3 add3;
    
    SC_CTOR (fullAdder) : add2 ("ADD2"), add3 ("ADD3") {
        add2.A (A0); add2.B (B0); add2.S (S0); add2.Cout (Cin);
        add3.A (A1); add3.B (B1); add3.S (S1); add3.Cout (Cout); add3.Cin (Cin);
    }      
};

#endif