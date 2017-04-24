#ifndef _STIM_H_
#define _STIM_H_

#include "systemc.h"

SC_MODULE (stim) {
    sc_out<bool> A0, A1, B0, B1;
    sc_in<bool> Clock;
    
    void stimGen() {
        A1.write (false); B1.write (false); A0.write (false); B0.write (false); wait();
        A1.write (false); B1.write (false); A0.write (false); B0.write (true); wait();
        A1.write (false); B1.write (false); A0.write (true); B0.write (false); wait();
        A1.write (false); B1.write (false); A0.write (true); B0.write (true); wait();
        
        A1.write (false); B1.write (true); A0.write (false); B0.write (false); wait();
        A1.write (false); B1.write (true); A0.write (false); B0.write (true); wait();
        A1.write (false); B1.write (true); A0.write (true); B0.write (false); wait();
        A1.write (false); B1.write (true); A0.write (true); B0.write (true); wait();
        
        A1.write (true); B1.write (false); A0.write (false); B0.write (false); wait();
        A1.write (true); B1.write (false); A0.write (false); B0.write (true); wait();
        A1.write (true); B1.write (false); A0.write (true); B0.write (false); wait();
        A1.write (true); B1.write (false); A0.write (true); B0.write (true); wait();
        
        A1.write (true); B1.write (true); A0.write (false); B0.write (false); wait();
        A1.write (true); B1.write (true); A0.write (false); B0.write (true); wait();
        A1.write (true); B1.write (true); A0.write (true); B0.write (false); wait();
        A1.write (true); B1.write (true); A0.write (true); B0.write (true); wait();
    
        sc_stop();
    }

    SC_CTOR (stim) {
        SC_THREAD (stimGen);
        sensitive << Clock.pos();
    }
};

#endif