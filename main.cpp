#include "systemc.h"
#include "stim.h"
#include "mon.h"
#include "fullAdder.h"

int sc_main (int argc, char* argv[]) {
    sc_signal <bool> A0s, A1s, B0s, B1s, S0s, S1s, Couts;
    
    sc_clock TestClk ("TestClock", 10, SC_NS, 0.5);
    
    stim Stimulus ("Stimulus");
    Stimulus.A0 (A0s); Stimulus.A1 (A1s); Stimulus.B0 (B0s); Stimulus.B1 (B1s); Stimulus.Clock (TestClk);
    
    fullAdder DUT ("Full_Adder");
    DUT.A0 (A0s); DUT.A1 (A1s); DUT.B0 (B0s); DUT.B1 (B1s); DUT.S0 (S0s); DUT.S1 (S1s); DUT.Cout (Couts);
    
    mon Monitor ("Monitor");
    Monitor.A0 (A0s); Monitor.A1 (A1s); Monitor.B0 (B0s); Monitor.B1 (B1s); Monitor.S0 (S0s); Monitor.S1 (S1s); Monitor.Cout (Couts); Monitor.Clock (TestClk);
    
    /*
    sc_trace_file* Tf;
    Tf = sc_create_vcd_trace_file("Traces");
    sc_trace(Tf, A1s , "A1" );
    sc_trace(Tf, B1s , "B1" );
    sc_trace(Tf, A0s , "A0" );
    sc_trace(Tf, B0s , "B0" );
    sc_trace(Tf, S0s , "S0" );
    sc_trace(Tf, Couts , "Cout" );
    sc_trace(Tf, S1s , "S1" );
    */
    
    sc_start();
    /*
    sc_close_vcd_trace_file(Tf);
    */
    
    return 0;
}
