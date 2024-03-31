#include <systemc.h>
#include "jpmic.h"

SC_MODULE(tb) {
    sc_in<bool> clk_in;
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
    SC_CTOR(tb) : clk_in("clk_in"),
                  pwrgd_inout("pwrgd_inout"),
                  vren_out("vren_out"),
                  wrb_out("wrb_out"),
                  bulk_out("bulk_out"),
                  addr_out("addr_out"),
                  data_out("data_out"),
                  v1p8_in("v1p8_in"),
                  v1p0_in("v1p0_in"),
                  railA_in("railA_in"),
                  railB_in("railB_in"),
                  railC_in("railC_in"),
                  data_in("data_in"),
                  gsi_n_in("gsi_n_in")
    {
        SC_CTHREAD(run, clk_in.pos());
    }
};
