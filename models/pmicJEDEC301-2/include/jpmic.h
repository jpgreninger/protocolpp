#ifndef JPMIC_H_
#define JPMIC_H_

///
///\class jpmic jpmic "include/jpmic.h"
///
///\section JPMIC Power Management IC model
///
/// Model for power management of DDR5 DIMMs with the following features
/// 
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTOR "AS IS" AND ANY
/// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
/// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
/// SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
/// OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
/// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
/// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
///

#include <iomanip>
#include <memory>
#include <systemc.h>
#include <vector>

#include "jdac.h"
#include "jrail.h"

class jpmic : public sc_module {

public:

    uint8_t m_stateint;

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
        uint32_t bulk_min_volt;
        uint32_t bulk_max_volt;
        uint32_t bulk_to_vren;
        uint32_t v18_pg_thresh;
        uint32_t v18_setting;
        uint32_t v10_pg_thresh;
        uint32_t v10_setting;
        uint32_t restart_time;
        uint32_t dac_samples;
        uint64_t dac_sample_time;
        int tInput_PWR_GOOD_GSI_Assertion;
        int tInput_OV_GSI_Assertion;
        int tInput_OV_VR_Disable;
        int tOutput_PWR_GOOD_GSI_Assertion;
        int tOutput_OV_VR_Disable;
        int tOutput_UV_VR_Disable;
        int tOutput_Current_Limiter;
        int tHigh_Temp_Warning;
        int tShut_Down_Temp;
        int tVIN_Bulk_to_VR_Enable;
        int t1p8V_Ready;
        int t1p0V_Ready;
        int tManagement_Ready;
        int tPMIC_PWR_Good_Out;
        int tPMIC_Output_Off;
        int tPWR_GOOD_Low_Pulse_Width;
        int tPWR_GOOD_Low_Pulse_Width_Filter;
        std::vector<jrail::railcfg> railcfg;
    };

    ////////////////////////////////////////////////////
    /// SystemC inout ports
    ////////////////////////////////////////////////////
    sc_inout_resolved pwrgd_inout;

    ////////////////////////////////////////////////////
    /// SystemC input ports
    ////////////////////////////////////////////////////
    sc_in<bool> clk_in;
    sc_in<bool> vren_in;
    sc_in<bool> wrb_in;
    sc_in<uint8_t> addr_in;
    sc_in<uint8_t> data_in;
    sc_in<uint32_t> bulk_in;

    ////////////////////////////////////////////////////
    /// SystemC output ports
    ////////////////////////////////////////////////////
    sc_out<bool> gsi_n_out;
    sc_out<uint8_t> data_out;
    sc_out<uint32_t> railA_out;
    sc_out<uint32_t> railB_out;
    sc_out<uint32_t> railC_out;
    sc_out<uint32_t> v1p8_out;
    sc_out<uint32_t> v1p0_out;

    ////////////////////////////////////////////////////
    /// internal wires
    ////////////////////////////////////////////////////
    sc_signal<bool> ldo_ramp_en;
    sc_buffer<bool> pwrsum_wire;
    sc_signal<bool> railA_en;
    sc_signal<bool> railB_en;
    sc_signal<bool> railC_en;
    sc_signal<bool> railA_update;
    sc_signal<bool> railB_update;
    sc_signal<bool> railC_update;
    sc_buffer<bool> railA_pwrgd;
    sc_buffer<bool> railB_pwrgd;
    sc_buffer<bool> railC_pwrgd;
    sc_buffer<bool> railA_zero;
    sc_buffer<bool> railB_zero;
    sc_buffer<bool> railC_zero;

    sc_buffer<uint8_t> dac_data_out;
    sc_buffer<uint8_t> cmd_in;
    sc_signal<uint8_t> temp_in;

    sc_signal<uint32_t> railA_volt;
    sc_signal<uint32_t> railB_volt;
    sc_signal<uint32_t> railC_volt;

    ////////////////////////////////////////////////////
    /// Constructor
    /// @param cfg - pmic configuration
    ////////////////////////////////////////////////////
    SC_CTOR(jpmic, pmicfg& cfg) : pwrgd_inout("pwrgd_inout"),
                                  clk_in("clk_in"),
                                  vren_in("vren_in"),
                                  wrb_in("wrb_in"),
                                  addr_in("addr_in"),
                                  data_in("data_in"),
                                  bulk_in("bulk_in"),
                                  gsi_n_out("gsi_n"),
                                  data_out("data_out"),
                                  railA_out("railA_out"),
                                  railB_out("railB_out"),
                                  railC_out("railC_out"),
                                  v1p8_out("v1p8_out"),
                                  v1p0_out("v1p0_out"),
                                  ldo_ramp_en("ldo_ramp_en", false),
                                  pwrsum_wire("pwrsum"),
                                  railA_en("railA_en", 0),
                                  railB_en("railB_en", 0),
                                  railC_en("railC_en", 0),
                                  railA_update("railA_update"),
                                  railB_update("railB_update"),
                                  railC_update("railC_update"),
                                  railA_pwrgd("railA_pwrgd"),
                                  railB_pwrgd("railB_pwrgd"),
                                  railC_pwrgd("railC_pwrgd"),
                                  railA_zero("railA_zero"),
                                  railB_zero("railB_zero"),
                                  railC_zero("railC_zero"),
                                  dac_data_out("dac_data_out"),
                                  cmd_in("cmd_in"),
                                  temp_in("temp_in", 105),
                                  railA_volt("railA_volt", 1100),
                                  railB_volt("railB_volt", 1100),
                                  railC_volt("railC_volt", 1800),
                                  m_state(pmic_state_t::P0),
                                  m_vren(false),
                                  m_vrdis(false),
                                  m_cfg(cfg),
                                  m_errcnt(0),
                                  m_errlog(0),
                                  m_v18(0),
                                  m_v10(0),
                                  m_ovr(false),
                                  m_uvr(false),
                                  m_bulk_gsi(false),
                                  m_bulk_ovr(false),
                                  m_bulk_uvr(false),
                                  m_limit(false),
                                  m_consum(false),
                                  m_shutdown(false),
                                  m_temp_warning(false),
                                  r32_locked(false),
                                  secured(false),
                                  unlocked(false),
                                  burn_memory(false),
                                  passwd0_wr(false),
                                  passwd1_wr(false),
                                  railA_ramp(true),
                                  railA_fault_mask(false),
                                  railB_ramp(true),
                                  railB_fault_mask(false),
                                  railC_ramp(true),
                                  railC_fault_mask(false),
                                  shutdn_inj(false),
                                  hi_temp_warn_inj(false),
                                  ldo_v18_pg_inj(false),
                                  hi_consump_inj(false),
                                  curr_limit_inj(false),
                                  swa_inj(false),
                                  swb_inj(false),
                                  swc_inj(false),
                                  bulk_inj(false),
                                  err_inject(false),
                                  ovrb_uvr_inj(false) {

        rails = std::make_shared<std::vector<jrail*>>();

        // default password
        passwd = {0x73, 0x94};

        // default register values from JEDEC301-2-1 spec
        m_regs = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x00-0x07
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x08-0x0F
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x20, 0x00, // 0x10-0x17
                  0x00, 0x04, 0x00, 0x05, 0x60, 0x00, 0x60, 0x60, // 0x18-0x1F
                  0x00, 0x78, 0x60, 0x00, 0x00, 0x78, 0x60, 0x78, // 0x20-0x27
                  0x60, 0x80, 0x89, 0x44, 0x20, 0x22, 0x04, 0x02, // 0x28-0x2F
                  0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, // 0x30-0x37
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x38-0x3F
                  0x01, 0x01, 0x01, 0x00, 0x00, 0x78, 0x60, 0x00, // 0x40-0x47
                  0x00, 0x78, 0x60, 0x78, 0x60, 0x80, 0x88, 0x00, // 0x48-0x4F
                  0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x50-0x57
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x22, 0x00, // 0x58-0x5F
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x60-0x67
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x68-0x6F
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x70-0x77
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x78-0x7F
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x80-0x87
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x88-0x8F
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x90-0x97
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x98-0x9F
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xA0-0xA7
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xA8-0xAF
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xB0-0xB7
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xB8-0xBF
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xC0-0xC7
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xC8-0xCF
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xD0-0xD7
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xD8-0xDF
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xE0-0xE7
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xE8-0xEF
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0xF0-0xF7
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};// 0xF8-0xFF

        // create and connect the rails
        railA = new jrail("railA", cfg.railcfg[0]);
        railA->enable_in(railA_en);
        railA->update_in(railA_update);
        railA->volt_in(railA_volt);
        railA->rail_out(railA_out);
        railA->pwrgd_out(railA_pwrgd);
        railA->zero_out(railA_zero);
        rails->push_back(railA);

        railB = new jrail("railB", cfg.railcfg[1]);
        railB->enable_in(railB_en);
        railB->update_in(railB_update);
        railB->volt_in(railB_volt);
        railB->rail_out(railB_out);
        railB->pwrgd_out(railB_pwrgd);
        railB->zero_out(railB_zero);
        rails->push_back(railB);

        railC = new jrail("railC", cfg.railcfg[2]);
        railC->enable_in(railC_en);
        railC->update_in(railC_update);
        railC->volt_in(railC_volt);
        railC->rail_out(railC_out);
        railC->pwrgd_out(railC_pwrgd);
        railC->zero_out(railC_zero);
        rails->push_back(railC);

        // create and connect the DAC
        dac = new jdac("dac", cfg.dac_samples, cfg.dac_sample_time, rails);
        dac->clk_in(clk_in);
        dac->cmd_in(cmd_in);
        dac->temp_in(temp_in);
        dac->bulk_in(bulk_in);
        dac->ldo18_in(v1p8_out);
        dac->ldo10_in(v1p0_out);
        dac->data_out(dac_data_out);
        dac->pwrsum_in(pwrsum_wire);

        // Register read/write are based on CLK_IN
        SC_THREAD(regs);
            sensitive << clk_in.pos() << wrb_in << addr_in << data_in;

        // monitor voltage
        SC_CTHREAD(volt_chk, clk_in.pos());

        // monitor current
        SC_CTHREAD(curr_chk, clk_in.pos());

        // monitor temperature
        SC_CTHREAD(temp_chk, clk_in.pos());

        // FSM needs to sensitive to CLK_IN but also to VREN and PWRGD pins
        SC_THREAD(fsm);
            sensitive << clk_in.pos() << vren_in << pwrgd_inout;

        // LDO ramp is controlled by ldo_ramp_en posedge or negedge
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
    /// monitor rail and bulk voltage (OVR/UVR)
    ////////////////////////////////////////////////////
    void volt_chk();

    ////////////////////////////////////////////////////
    /// monitor rail current (LIMITER/CONSUMPTION)
    ////////////////////////////////////////////////////
    void curr_chk();

    ////////////////////////////////////////////////////
    /// monitor die temperature
    ////////////////////////////////////////////////////
    void temp_chk();

    ////////////////////////////////////////////////////
    /// run the pmic
    ////////////////////////////////////////////////////
    void fsm();

    ////////////////////////////////////////////////////
    /// ramp output LDOs
    ////////////////////////////////////////////////////
    void ldo_ramp();

    ////////////////////////////////////////////////////
    /// registers
    ////////////////////////////////////////////////////
    std::array<uint8_t, 256> m_regs;

    bool railA_fault_mask;
    pmic_state_t m_state;

private:

    bool m_vren;
    bool m_vrdis;
    pmicfg m_cfg;
    uint8_t m_errcnt;
    uint8_t m_errlog;
    uint32_t m_v18, m_v10;
    std::array<uint8_t, 2> passwd;
    std::shared_ptr<std::vector<jrail*>> rails;
    bool m_ovr;
    bool m_uvr;
    bool m_bulk_gsi;
    bool m_bulk_ovr;
    bool m_bulk_uvr;
    bool m_limit;
    bool m_consum;
    bool m_shutdown;
    bool m_temp_warning;
    bool r32_locked;
    bool secured;
    bool unlocked;
    bool burn_memory;
    bool passwd0_wr;
    bool passwd1_wr;
    bool railA_ramp;
    bool railB_ramp;
    bool railB_fault_mask;
    bool railC_ramp;
    bool railC_fault_mask;
    bool shutdn_inj;
    bool hi_temp_warn_inj;
    bool ldo_v18_pg_inj;
    bool hi_consump_inj;
    bool curr_limit_inj;
    bool swa_inj;
    bool swb_inj;
    bool swc_inj;
    bool bulk_inj;
    bool err_inject;
    bool ovrb_uvr_inj;
    bool tInput_PWR_GOOD_GSI_Assertion_trigger;
    bool tOutput_PWR_GOOD_GSI_Assertion_trigger;
    bool tVIN_Bulk_to_VR_Enable_trigger;
    bool t1p8V_Ready_trigger;
    bool t1p0V_Ready_trigger;
    bool tManagement_Ready_trigger;
    bool tPMIC_PWR_Good_Out_trigger;
    bool tPMIC_Output_Off_trigger;
    bool tPWR_GOOD_Low_Pulse_Width_trigger;
    bool tPWR_GOOD_Low_Pulse_Width_Filter_trigger;
};

#endif // JPMIC_H_
