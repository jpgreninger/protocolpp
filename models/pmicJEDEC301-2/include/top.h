#include <systemc.h>
#include "tb.h"
#include "jpmic.h"
#include "jrail.h"

SC_MODULE(TOP) {
    tb *tb0;
    jpmic *pmic;

    sc_clock clk_in;
    sc_signal<bool> vren_in;
    sc_signal<bool> pwrgd;
    sc_buffer<bool> gsi_n;
    sc_buffer<bool> wrb;
    sc_buffer<uint8_t> addr_in;
    sc_buffer<uint8_t> data_in;
    sc_buffer<uint32_t> bulk_out;
    sc_buffer<uint32_t> railA_out;
    sc_buffer<uint32_t> railB_out;
    sc_buffer<uint32_t> railC_out;
    sc_buffer<uint32_t> v1p8_out;;
    sc_buffer<uint32_t> v1p0_out;
    sc_buffer<uint8_t> data_out;

    // instantiate rail
    SC_CTOR(TOP) : clk_in("clk_in"),
                   vren_in("vren_in"),
                   pwrgd("pwrgd"),
                   gsi_n("gsi_n"),
                   wrb("wrb"),
                   addr_in("addr_in"),
                   data_in("data_in"),
                   bulk_out("bulk_out"),
                   railA_out("railA_out"),
                   railB_out("railB_out"),
                   railC_out("railC_out"),
                   v1p8_out("v1p8_out"),
                   v1p0_out("v1p0_out"),
                   data_out("data_out") {
        // rail configurations
        std::vector<jrail::railcfg> railcfg;
        railcfg.emplace_back(1100, 0.275, 6000, 4000, 24000, 1100, 2200, 6000, 0);
        railcfg.emplace_back(1100, 0.275, 6000, 4000, 24000, 1100, 2200, 3000, 500);
        railcfg.emplace_back(1800, 1.800, 6000, 2000, 12000, 1800, 1800, 0, 1000);

        // PMIC configuration
        jpmic::pmicfg cfg;
    
        // populate the PMIC configuration
        cfg.bulk_pg_thresh = 4250;
        cfg.bulk_max_volt = 6000;
        cfg.bulk_to_vren = 8;
        cfg.v18_pg_thresh = 1600;
        cfg.v18_setting = 1800;
        cfg.v10_pg_thresh = 900;
        cfg.v10_setting = 1000;
        cfg.restart_time = 10000;
        cfg.dac_samples = 8;
        cfg.dac_sample_time = 1000000; // nanoseconds (1ms = 1000000ns)
        cfg.railcfg = railcfg;

        // connect testbench
        tb0 = new tb("tb");

        // outputs
        tb0->clk_in(clk_in);
        tb0->vren_out(vren_in);
        tb0->pwrgd_inout(pwrgd);
        tb0->bulk_out(bulk_out);
        tb0->wrb_out(wrb);
        tb0->addr_out(addr_in);
        tb0->data_out(data_in);

        // inputs
        tb0->v1p8_in(v1p8_out);
        tb0->v1p0_in(v1p0_out);
        tb0->railA_in(railA_out);
        tb0->railB_in(railB_out);
        tb0->railC_in(railC_out);
        tb0->data_in(data_out);
        tb0->gsi_n_in(gsi_n);

        // connect rail
        pmic = new jpmic("pmic", cfg);

        // inputs
        pmic->clk_in(clk_in);
        pmic->wrb_in(wrb);
        pmic->vren_in(vren_in);
        pmic->pwrgd_inout(pwrgd);
        pmic->bulk_in(bulk_out);
        pmic->addr_in(addr_in);
        pmic->data_in(data_in);

        // outputs
        pmic->railA_out(railA_out);
        pmic->railB_out(railB_out);
        pmic->railC_out(railC_out);
        pmic->v1p8_out(v1p8_out);
        pmic->v1p0_out(v1p0_out);
        pmic->data_out(data_out);
        pmic->gsi_n_out(gsi_n);
    }
};
