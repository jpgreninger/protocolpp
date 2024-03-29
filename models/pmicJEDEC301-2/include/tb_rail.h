#include <systemc.h>
#include "jrail.h"

SC_MODULE(tb_rail) {
    sc_out<bool> enable_out;
    sc_out<uint32_t> volt_out;
    sc_in<uint32_t> rail_in;

    void run_rail();

    // instantiate rail
    SC_CTOR(tb_rail) {
        SC_THREAD(run_rail);
    }
};
