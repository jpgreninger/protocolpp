#include <systemc.h>
#include "jrail.h"

SC_MODULE(tb_rail) {
    sc_out<bool> enable_out;
    sc_out<bool> update_out;
    sc_out<uint32_t> volt_out;
    sc_in<bool> pwrgd_in;
    sc_in<bool> zero_in; 
    sc_in<uint32_t> rail_in;

    void run_rail();

    // instantiate rail
    SC_CTOR(tb_rail) : enable_out("enable_out"),
                       update_out("update_out"),
                       volt_out("volt_out"),
                       pwrgd_in("pwrgd_in"),
                       zero_in("zero_in"),
                       rail_in("rail_in") {
        SC_THREAD(run_rail);
    }
};
