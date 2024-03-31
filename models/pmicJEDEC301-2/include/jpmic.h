#ifndef JPMIC_H_
#define JPMIC_H_

#include <deque>
#include <memory>
#include <systemc.h>
#include <thread>
#include <vector>

#include "jdac.h"
#include "jrail.h"

class jpmic : public sc_module {

public:

    jrail* railA;
    jrail* railB;
    jrail* railC;
    jdac* dac;

    enum pmic_state_t {
        P0,
        P1,
        P2_A1,
        P2_A2,
        P2_B,
        RAMPUP,
        RAMPDN,
        P3
    };

    enum pmicreg_t {
        R1A = 0x1A,
        R2F = 0x2F,
        R32 = 0x32,
        ENABLE = 0xFF
    };

    ////////////////////////////////////////////////////
    /// PMIC configuration structure
    /// @param restart_time - time to wait before restart after error or power cycle
    /// @param dac_samples - number of sample for the DAC
    /// @param dac_sample_time - sample time for DAC
    /// @param railcfg - configurations for rails and temperature sensors
    ////////////////////////////////////////////////////
    struct pmicfg {
        uint32_t bulk_pg_thresh;
        uint32_t bulk_max_volt;
        uint32_t bulk_to_vren;
        uint32_t v18_pg_thresh;
        uint32_t v18_setting;
        uint32_t v10_pg_thresh;
        uint32_t v10_setting;
        uint32_t restart_time;
        uint32_t dac_samples;
        uint64_t dac_sample_time;
        std::vector<jrail::railcfg> railcfg;
    };

    // ports
    sc_in<bool> clk_in;
    sc_in<bool> wrb_in;
    sc_in<bool> vren_in;
    sc_out<bool> gsi_n_out;
    sc_inout<bool> pwrgd_inout;

    sc_in<uint32_t> bulk_in;
    sc_in<uint8_t> addr_in;
    sc_in<uint8_t> data_in;

    sc_out<uint32_t> railA_out;
    sc_out<uint32_t> railB_out;
    sc_out<uint32_t> railC_out;

    sc_out<uint32_t> v1p8_out;
    sc_out<uint32_t> v1p0_out;
    sc_out<uint8_t> data_out;

    // wires
    sc_signal<uint32_t> railA_volt;
    sc_signal<uint32_t> railB_volt;
    sc_signal<uint32_t> railC_volt;

    sc_buffer<uint8_t> dac_data_out;
    sc_buffer<uint8_t> cmd_in;
    sc_buffer<bool> rail_en;
    sc_buffer<bool> pwrsum_wire;
    sc_signal<bool> ldo_ramp_en;

    sc_buffer<bool> railA_pwrgd;
    sc_buffer<bool> railB_pwrgd;
    sc_buffer<bool> railC_pwrgd;

    sc_buffer<bool> railA_zero;
    sc_buffer<bool> railB_zero;
    sc_buffer<bool> railC_zero;

    ////////////////////////////////////////////////////
    /// Constructor
    /// @param cfg - pmic configuration
    /// @param clk - clock object
    ////////////////////////////////////////////////////
    SC_CTOR(jpmic, pmicfg& cfg) : clk_in("clk_in"),
                                  wrb_in("wrb_in"),
                                  vren_in("vren_in"),
                                  gsi_n_out("gsi_n"),
                                  pwrgd_inout("pwrgd_inou"),
                                  bulk_in("bulk_in"),
                                  addr_in("addr_in"),
                                  data_in("data_in"),
                                  railA_out("railA_out"),
                                  railB_out("railB_out"),
                                  railC_out("railC_out"),
                                  v1p8_out("v1p8_out"),
                                  v1p0_out("v1p0_out"),
                                  data_out("data_out"),
                                  railA_volt("railA_volt_in", 1100),
                                  railB_volt("railB_volt_in", 1100),
                                  railC_volt("railC_volt_in", 1800),
                                  cmd_in("cmd_in"),
                                  rail_en("rail_en"),
                                  pwrsum_wire("pwrsum"),
                                  ldo_ramp_en("ldo_ramp_en", 0),
                                  railA_pwrgd("railA_pwrgd"),
                                  railB_pwrgd("railB_pwrgd"),
                                  railC_pwrgd("railC_pwrgd"),
                                  railA_zero("railA_zero"),
                                  railB_zero("railB_zero"),
                                  railC_zero("railC_zero"),
                                  m_state(pmic_state_t::P0),
                                  m_bulk_valid(false),
                                  m_vren(false),
                                  m_vrdis(false),
                                  m_error(false),
                                  m_cfg(cfg),
                                  m_v18(0),
                                  m_v10(0) {

        rails = std::make_shared<std::vector<jrail*>>();

        // default register values from JEDEC301-2-1 spec
        m_regs = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x20, 0x00,
                  0x00, 0x04, 0x00, 0x05, 0x60, 0x00, 0x60, 0x60,
                  0x00, 0x78, 0x60, 0x00, 0x00, 0x78, 0x60, 0x78,
                  0x60, 0x80, 0x89, 0x44, 0x20, 0x22, 0x04, 0x02,
                  0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x01, 0x01, 0x01, 0x00, 0x00, 0x78, 0x60, 0x00,
                  0x00, 0x78, 0x60, 0x78, 0x60, 0x80, 0x88, 0x00,
                  0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x22, 0x00};

        // create the rails
        railA = new jrail("railA", cfg.railcfg[0]);
        railA->clk_in(clk_in);
        railA->enable_in(rail_en);
        railA->volt_in(railA_volt);
        railA->rail_out(railA_out);
        railA->pwrgd_out(railA_pwrgd);
        railA->zero_out(railA_zero);
        rails->push_back(railA);

        railB = new jrail("railB", cfg.railcfg[1]);
        railB->clk_in(clk_in);
        railB->enable_in(rail_en);
        railB->volt_in(railB_volt);
        railB->rail_out(railB_out);
        railB->pwrgd_out(railB_pwrgd);
        railB->zero_out(railB_zero);
        rails->push_back(railB);

        railC = new jrail("railC", cfg.railcfg[2]);
        railC->clk_in(clk_in);
        railC->enable_in(rail_en);
        railC->volt_in(railC_volt);
        railC->rail_out(railC_out);
        railC->pwrgd_out(railC_pwrgd);
        railC->zero_out(railC_zero);
        rails->push_back(railC);

        // add the DAC
        dac = new jdac("dac", cfg.dac_samples, cfg.dac_sample_time, rails);
        dac->clk_in(clk_in);
        dac->cmd_in(cmd_in);
        dac->data_out(dac_data_out);
        dac->pwrsum_in(pwrsum_wire);

        SC_CTHREAD(run, clk_in.pos());
        SC_CTHREAD(regs, clk_in.pos());
        SC_THREAD(ldo_ramp);
            sensitive << ldo_ramp_en;
    }

    ////////////////////////////////////////////////////
    /// Destructor
    ////////////////////////////////////////////////////
    ~jpmic() = default;

    ////////////////////////////////////////////////////
    /// write register values
    ////////////////////////////////////////////////////
    void regs();

    ////////////////////////////////////////////////////
    /// run the pmic
    ////////////////////////////////////////////////////
    void run();

    ////////////////////////////////////////////////////
    /// ramp output LDOs
    ////////////////////////////////////////////////////
    void ldo_ramp();

private:

    pmic_state_t m_state;
    bool m_bulk_valid;
    bool m_vren;
    bool m_vrdis;
    bool m_error;
    pmicfg m_cfg;
    uint32_t m_v18, m_v10;
    std::shared_ptr<std::vector<jrail*>> rails;
    std::array<uint8_t, 96> m_regs;
};

#endif // JPMIC_H_
