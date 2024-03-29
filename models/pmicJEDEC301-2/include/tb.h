#include <systemc.h>
#include "jpmic.h"

SC_MODULE(tb) {
    sc_in<bool> pwrgd_inout;

    sc_out<bool> vren_out;
    sc_out<bool> wrb_out;
    sc_out<uint32_t> bulk_out;
    sc_out<uint8_t> addr_out;
    sc_out<uint8_t> data_out;

    sc_in<uint32_t> v1p8_in;
    sc_in<uint32_t> v1p0_in;
    sc_in<uint32_t> railA_in;
    sc_in<uint32_t> railB_in;
    sc_in<uint32_t> railC_in;
    sc_in<uint8_t> data_in;
    sc_in<bool> gsi_n_in;

    void run();

    // instantiate rail
    SC_CTOR(tb) {
        SC_THREAD(run);
    }
};
