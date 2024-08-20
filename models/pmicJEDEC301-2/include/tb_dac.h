#include <systemc.h>
#include "jdac.h"
#include "jrail.h"

SC_MODULE(tb_dac) {
    sc_out<bool> railA_en;
    sc_out<bool> railB_en;
    sc_out<bool> railC_en;
    sc_out<bool> railA_up;
    sc_out<bool> railB_up;
    sc_out<bool> railC_up;
    sc_out<bool> pwrsum_out;
    sc_out<uint32_t> railA_volt;
    sc_out<uint32_t> railB_volt;
    sc_out<uint32_t> railC_volt;
    sc_out<uint8_t> cmd_out;
    sc_out<uint8_t> temp_out;
    sc_out<uint32_t> bulk_out;
    sc_out<uint32_t> ldo18_out;
    sc_out<uint32_t> ldo10_out;
    sc_in<uint8_t> data_in;
    sc_in<bool> railA_pwrgd;
    sc_in<bool> railB_pwrgd;
    sc_in<bool> railC_pwrgd;
    sc_in<bool> railA_zero;
    sc_in<bool> railB_zero;
    sc_in<bool> railC_zero;

    void run();

    // instantiate rail
    SC_CTOR(tb_dac) : railA_en("railA_en"),
                      railB_en("railB_en"),
                      railC_en("railC_en"),
                      railA_up("railA_up"),
                      railB_up("railB_up"),
                      railC_up("railC_up"),
                      pwrsum_out("pwrsum_out"),
                      railA_volt("railA_volt"),
                      railB_volt("railB_volt"),
                      railC_volt("railC_volt"),
                      cmd_out("cmd_out"),
                      temp_out("temp_out"),
                      bulk_out("bulk_out"),
                      ldo18_out("ldo18_out"),
                      ldo10_out("ldo10_out"),
                      data_in("data_in"),
                      railA_pwrgd("railA_pwrgd"),
                      railB_pwrgd("railB_pwrgd"),
                      railC_pwrgd("railC_pwrgd"),
                      railA_zero("railA_zero"),
                      railB_zero("railB_zero"),
                      railC_zero("railC_zero")
    {
        SC_THREAD(run);
    }
};
