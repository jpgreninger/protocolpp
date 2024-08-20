#include <systemc.h>
#include <memory>
#include <vector>
#include "tb_dac.h"
#include "jdac.h"
#include "jrail.h"

SC_MODULE(TOPDAC) {
    std::shared_ptr<std::vector<jrail*>> rails;
    tb_dac *tb;
    jrail *railA;
    jrail *railB;
    jrail *railC;
    jdac *dac;

    sc_clock clk_in;
    sc_buffer<bool> railA_en_wire;
    sc_buffer<bool> railB_en_wire;
    sc_buffer<bool> railC_en_wire;
    sc_buffer<bool> railA_up_wire;
    sc_buffer<bool> railB_up_wire;
    sc_buffer<bool> railC_up_wire;
    sc_buffer<bool> railA_pwrgd_wire;
    sc_buffer<bool> railB_pwrgd_wire;
    sc_buffer<bool> railC_pwrgd_wire;
    sc_buffer<bool> railA_zero_wire;
    sc_buffer<bool> railB_zero_wire;
    sc_buffer<bool> railC_zero_wire;
    sc_buffer<bool> pwrsum_wire;
    sc_buffer<uint8_t> cmd_out_wire;
    sc_buffer<uint8_t> data_in_wire;
    sc_buffer<uint8_t> temp_in_wire;
    sc_buffer<uint32_t> bulk_in_wire;
    sc_buffer<uint32_t> ldo18_in_wire;
    sc_buffer<uint32_t> ldo10_in_wire;
    sc_buffer<uint32_t> railA_volt_wire;
    sc_buffer<uint32_t> railB_volt_wire;
    sc_buffer<uint32_t> railC_volt_wire;
    sc_buffer<uint32_t> railA_out_wire;
    sc_buffer<uint32_t> railB_out_wire;
    sc_buffer<uint32_t> railC_out_wire;

    // instantiate rail
    SC_CTOR(TOPDAC) {
        rails = std::make_shared<std::vector<jrail*>>();

        // rail configurations
        jrail::railcfg railcfgA(1100, 0.275, 6000, 4000, 24000, 550, 2200, 4000, 0);
        jrail::railcfg railcfgB(1100, 0.275, 6000, 4000, 24000, 550, 2200, 4000, 0);
        jrail::railcfg railcfgC(1800, 1.800, 6000, 2000, 12000, 900, 1800, 0, 0);

        // connect testbench
        tb = new tb_dac("tb_dac");

        // outputs
        tb->railA_en(railA_en_wire);
        tb->railB_en(railB_en_wire);
        tb->railC_en(railC_en_wire);
        tb->railA_up(railA_up_wire);
        tb->railB_up(railB_up_wire);
        tb->railC_up(railC_up_wire);
        tb->railA_pwrgd(railA_pwrgd_wire);
        tb->railB_pwrgd(railB_pwrgd_wire);
        tb->railC_pwrgd(railC_pwrgd_wire);
        tb->railA_zero(railA_zero_wire);
        tb->railB_zero(railB_zero_wire);
        tb->railC_zero(railC_zero_wire);
        tb->railA_volt(railA_volt_wire);
        tb->railB_volt(railB_volt_wire);
        tb->railC_volt(railC_volt_wire);
        tb->cmd_out(cmd_out_wire);
        tb->data_in(data_in_wire);
        tb->pwrsum_out(pwrsum_wire);
        tb->temp_out(temp_in_wire);
        tb->bulk_out(bulk_in_wire);
        tb->ldo18_out(ldo18_in_wire);
        tb->ldo10_out(ldo10_in_wire);

        // connect rail
        railA = new jrail("railA", railcfgA);
        railB = new jrail("railB", railcfgB);
        railC = new jrail("railC", railcfgC);

        // inputs
        railA->enable_in(railA_en_wire);
        railA->update_in(railA_up_wire);
        railA->volt_in(railA_volt_wire);
        railA->rail_out(railA_out_wire);
        railA->pwrgd_out(railA_pwrgd_wire);
        railA->zero_out(railA_zero_wire);

        railB->enable_in(railB_en_wire);
        railB->update_in(railB_up_wire);
        railB->volt_in(railB_volt_wire);
        railB->rail_out(railB_out_wire);
        railB->pwrgd_out(railB_pwrgd_wire);
        railB->zero_out(railB_zero_wire);

        railC->enable_in(railC_en_wire);
        railC->update_in(railC_up_wire);
        railC->volt_in(railC_volt_wire);
        railC->rail_out(railC_out_wire);
        railC->pwrgd_out(railC_pwrgd_wire);
        railC->zero_out(railC_zero_wire);

        // add rails to vector
        rails->push_back(railA);
        rails->push_back(railB);
        rails->push_back(railC);

        // connect dac
        dac = new jdac("dac", 8, 50, rails);
        dac->clk_in(clk_in);
        dac->cmd_in(cmd_out_wire);
        dac->temp_in(temp_in_wire);
        dac->data_out(data_in_wire);
        dac->pwrsum_in(pwrsum_wire);
        dac->bulk_in(bulk_in_wire);
        dac->ldo18_in(ldo18_in_wire);
        dac->ldo10_in(ldo10_in_wire);
    }
};
