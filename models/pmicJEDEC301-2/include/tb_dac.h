#include <systemc.h>
#include "jdac.h"
#include "jrail.h"

SC_MODULE(tb_dac) {
    sc_out<bool> railA_en;
    sc_out<bool> railB_en;
    sc_out<bool> railC_en;
    sc_out<bool> pwrsum_out;
    sc_out<uint32_t> railA_volt;
    sc_out<uint32_t> railB_volt;
    sc_out<uint32_t> railC_volt;
    sc_out<uint8_t> cmd_out;
    sc_in<uint8_t> data_in;

    void run();

    // instantiate rail
    SC_CTOR(tb_dac) {
        SC_THREAD(run);
    }
};
