#ifndef _MON_H_
#define _MON_H_

#include "systemc.h"
#include <iomanip>
using namespace std;

SC_MODULE (mon) {
    sc_in<bool> A0, A1, B0, B1, S0, S1, Cout, Clock;
    
    void monitor() {
        cout << setw (10) << "Time";
        cout << setw (5) << "A1";
        cout << setw (5) << "B1";
        cout << setw (5) << "A0";
        cout << setw (5) << "B0";
        cout << setw (5) << "S0"; 
        cout << setw (5) << "Cout";
        cout << setw (5) << "S1" << endl;
    
        while (true) {
            cout << setw (10) << sc_time_stamp();
            cout << setw (5) << A1.read();
            cout << setw (5) << B1.read();
            cout << setw (5) << A0.read();
            cout << setw (5) << B0.read();
            cout << setw (5) << S0.read();
            cout << setw (5) << Cout.read();
            cout << setw (5) << S1.read() << endl;
            wait();
        }
    }

    SC_CTOR (mon) {
        SC_THREAD (monitor);
        sensitive << Clock.pos();
    }      
};

#endif