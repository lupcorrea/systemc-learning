#ifndef _MON_H_
#define _MON_H_

#include "systemc.h"
#include <iomanip>
using namespace std;

SC_MODULE (mon) {
    sc_in< sc_int<64> > A, B, Sum, Mul;
    sc_in<bool> Clock;
    
    void monitor() {
        cout << setw (10) << "Time";
        cout << setw (10) << "A";
        cout << setw (10) << "B";
        cout << setw (10) << "Sum";
        cout << setw (10) << "Mul" << endl;
        
        while (true) {
            cout << setw (10) << sc_time_stamp();
            cout << setw (10) << A.read();
            cout << setw (10) << B.read();
            cout << setw (10) << Sum.read();
            cout << setw (10) << Mul.read() << endl;
            wait();
        }
    }

    SC_CTOR (mon) {
        SC_THREAD (monitor);
        sensitive << Clock.pos();
    }      
};

#endif