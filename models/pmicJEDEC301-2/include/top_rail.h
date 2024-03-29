#include <systemc.h>
#include "tb_rail.h"
#include "jrail.h"

SC_MODULE(TOPRAIL) {
    tb_rail *tb;
    jrail *rail;

    sc_buffer<bool> enable_wire;
    sc_buffer<uint32_t> volt_wire;
    sc_buffer<uint32_t> rail_wire;

    // instantiate rail
    SC_CTOR(TOPRAIL) {
        // rail configurations
        jrail::railcfg railcfg(1100, 100, 6000, 4000, 24000, 550, 550, 2000, 0);

        // connect testbench
        tb = new tb_rail("rail");

        // outputs
        tb->enable_out(enable_wire);
        tb->volt_out(volt_wire);
        tb->rail_in(rail_wire);

        // connect rail
        rail = new jrail("rail", railcfg);

        // inputs
        rail->enable_in(enable_wire);
        rail->volt_in(volt_wire);
        rail->rail_out(rail_wire);
    }
};
