#include "jpmic.h"

// Reset the device (cold, hard, soft)
void jpmic::regs() {
    while(true) {
        wait();

        bool wrb = wrb_in.read();
        uint8_t addr = addr_in.read();
        uint8_t data = data_in.read();
        bool secured = ((((m_regs[0x2F] & 0x04) == 0) && ((m_regs[0x32] & 0x80) == 0x80)) ? true : false);

        if (secured &&
           (((addr >= 0x15) && (addr <= 0x2F)) ||
           ((addr >= 0x40) && (addr <= 0x6F)) || (addr == 0x32))) {
            if (!wrb) {
                data_out.write(m_regs[addr]);
            }
        }
        else if (wrb){
            switch(addr) {
                case 0x00:
                case 0x01:
                case 0x02:
                case 0x03:
                case 0x04:
                case 0x05:
                case 0x06:
                case 0x07:
                case 0x08:
                case 0x09:
                case 0x0A:
                case 0x0B:
                case 0x0C:
                case 0x0D:
                case 0x0E:
                case 0x0F:
                    // RO registers
                    break;
                case 0x1A:
                    m_regs[0x1A] = data;

                    // enable power summation
                    if ((m_regs[0x1B] & 0x40) && (data & 0x02)) {
                        pwrsum_wire.write(true);
                    }
                    else {
                        pwrsum_wire.write(false);
                    }
                    break;
                case 0x21:
                    // change the rail voltage
                    if ((m_regs[0x21] & 0xFE) != (data & 0xFE)) {
                        railA_volt.write((800 + (5 * (data & 0xFE))));
                        railA_update.write(true);
                    }
    
                    m_regs[0x21] = data;
                    break;
                case 0x25:
                    // change the rail voltage
                    if ((m_regs[0x25] & 0xFE) != (data & 0xFE)) {
                        railB_volt.write((800 + (5 * (data & 0xFE))));
                        railB_update.write(true);
                    }
    
                    m_regs[0x25] = data;
                    break;
                case 0x27:
                    // change the rail voltage
                    if ((m_regs[0x27] & 0xFE) != (data & 0xFE)) {
                        railC_volt.write((1500 + (5 * (data & 0xFE))));
                        railC_update.write(true);
                    }
    
                    m_regs[0x27] = data;
                    break;
                case 0x2F: {
                    m_regs[0x2F] = data;
                    break;
                }
                case 0x30: {
                    m_regs[addr] = data;

                    if (data & 0x80) {
                        uint32_t railVolt = 0;
                        switch(data & 0x78) {
                            case 0:
                                railVolt = railA_out.read();
                                m_regs[0x31] = ((railVolt >= 3875) ? 0xFF : railVolt/15);
                                break;
                            case 2:
                                railVolt = railB_out.read();
                                m_regs[0x31] = ((railVolt >= 3875) ? 0xFF : railVolt/15);
                                break;
                            case 3:
                                railVolt = railC_out.read();
                                m_regs[0x31] = ((railVolt >= 3875) ? 0xFF : railVolt/15);
                                break;
                            case 5:
                                railVolt = bulk_in->read();
                                m_regs[0x31] = ((railVolt >= 17850) ? 0xFF : railVolt/70);
                                break;
                            case 8:
                                m_regs[0x31] = ((m_v18 >= 3875) ? 0xFF : m_v18/15);
                                break;
                            case 9:
                                m_regs[0x31] = ((m_v10 >= 3875) ? 0xFF : m_v10/15);
                                break;
                            default:
                                m_regs[0x31] = 0;
                        }
                    }
                    break;
                }
                case 0x31:
                    // RO register
                    break;
                case 0x32: {
                    if((data & 0x80) && !(m_regs[addr] & 0x80)) {
                        m_vren = true;
                    }
                    else if(!(data & 0x80) && (m_regs[addr] & 0x80)) {
                        m_vrdis = true;
                    }

                    m_regs[addr] = data;
                    break;
                }
                case 0x33:
                case 0x34:
                    // RO register
                    break;
                case 0x3B:
                case 0x3C:
                case 0x3D:
                    // RO register
                    break;
                default:
                    m_regs[addr] = data;
            }
        }
        else {
            switch(addr) {
                case 0x37:
                case 0x38:
                    // WO registers
                    break;
                default:
                    data_out.write(m_regs[addr]);
            }
        }
    }
}

void jpmic::volt_chk() {
    bool m_ovrA=false;
    bool m_ovrB=false;
    bool m_ovrC=false;

    bool m_uvrA=false;
    bool m_uvrB=false;
    bool m_uvrC=false;

    while (true) {
        wait();

        int railA_setting = (800 + (5 * ((m_regs[0x21] & 0xFE) >> 1)));
        int railB_setting = (800 + (5 * ((m_regs[0x25] & 0xFE) >> 1)));
        int railC_setting = (1500 + (5 * ((m_regs[0x27] & 0xFE) >> 1)));

        // read the voltage
        int railA_vout = rails->at(0)->voltage();
        int railB_vout = rails->at(1)->voltage();
        int railC_vout = rails->at(2)->voltage();

        // read bulk in
        uint32_t bulk_in_read = bulk_in.read();

        // SWA OVR
        switch(m_regs[0x22] & 0x30) {
            case 0x00:
                m_ovrA = (railA_vout > (railA_setting + (railA_setting * 0.0075)));
                break;
            case 0x10:
                m_ovrA = (railA_vout > (railA_setting + (railA_setting * 0.01)));
                break;
            case 0x20:
                m_ovrA = (railA_vout > (railA_setting + (railA_setting * 0.0125)));
                break;
            default:
                m_ovrA = false;
        }

        // SWA UVR
        switch(m_regs[0x22] & 0x0C) {
            case 0x00:
                m_uvrA = (railA_vout < (railA_setting - (railA_setting * 0.010)));
                break;
            case 0x04:
                m_uvrA = (railA_vout < (railA_setting - (railA_setting * 0.0125)));
                break;
            default:
                m_uvrA = false;
        }

        // SWB OVR
        switch(m_regs[0x26] & 0x30) {
            case 0x00:
                m_ovrB = (railB_vout > (railB_setting + (railB_setting * 0.0075)));
                break;
            case 0x10:
                m_ovrB = (railA_vout > (railA_setting + (railA_setting * 0.01)));
                break;
            case 0x20:
                m_ovrB = (railA_vout > (railA_setting + (railA_setting * 0.0125)));
                break;
            default:
                m_ovrB = false;
        }

        // SWA UVR
        switch(m_regs[0x26] & 0x0C) {
            case 0x00:
                m_uvrB = (railB_vout < (railB_setting - (railB_setting * 0.010)));
                break;
            case 0x04:
                m_uvrA = (railB_vout < (railB_setting - (railB_setting * 0.0125)));
                break;
            default:
                m_uvrB = false;
        }

        // SWC OVR
        switch(m_regs[0x28] & 0x30) {
            case 0x00:
                m_ovrC = (railC_vout > (railC_setting + (railC_setting * 0.0075)));
                break;
            case 0x10:
                m_ovrC = (railC_vout > (railC_setting + (railC_setting * 0.01)));
                break;
            case 0x20:
                m_ovrC = (railC_vout > (railC_setting + (railC_setting * 0.0125)));
                break;
            default:
                m_ovrC = false;
        }

        // SWC UVR
        switch(m_regs[0x28] & 0x0C) {
            case 0x00:
                m_uvrC = (railC_vout < (railC_setting - (railC_setting * 0.010)));
                break;
            case 0x04:
                m_uvrC = (railC_vout < (railC_setting - (railC_setting * 0.0125)));
                break;
            default:
                m_uvrC = false;
        }

        // rail OVR/UVR
        m_ovr = m_ovrA | m_ovrB | m_ovrC;
        m_uvr = m_uvrA | m_uvrB | m_uvrC;

        // bulk input OVR/UVR
        m_bulk_ovr = bulk_in_read > m_cfg.bulk_max_volt;
        m_bulk_uvr = bulk_in_read < m_cfg.bulk_min_volt;
    }
}

void jpmic::curr_chk() {
    bool m_limitA=false;
    bool m_limitB=false;
    bool m_limitC=false;
    bool m_consumA=false;
    bool m_consumB=false;
    bool m_consumC=false;

    while (true) {
        wait();

        // rail curent limiter setting
        int railA_limit = (3000 + (500 * ((m_regs[0x20] & 0xC0) >> 6)));
        int railB_limit = (3000 + (500 * ((m_regs[0x20] & 0x0C) >> 2)));
        int railC_limit = (500 + (500 * (m_regs[0x20] & 0x03)));

        // rail current consumption setting
        int railA_consump = (125 * ((m_regs[0x1C] & 0xFC) >> 2));
        int railB_consump = (125 * ((m_regs[0x1E] & 0xFC) >> 2));
        int railC_consump = (125 * ((m_regs[0x1F] & 0xFC) >> 2));

        // read the current
        int railA_curr = rails->at(0)->current();
        int railB_curr = rails->at(1)->current();
        int railC_curr = rails->at(2)->current();

        // SWA current limiter
        m_limitA = railA_curr > railA_limit;

        // SWA current consumption
        m_consumA = railA_curr > railA_consump;

        // SWB current limiter
        m_limitB = railB_curr > railB_limit;

        // SWB current consumption
        m_consumB = railB_curr > railB_consump;

        // SWC current limiter
        m_limitC = railC_curr > railC_limit;

        // SWC current consumption
        m_consumC = railC_curr > railC_consump;

        // rail OVR/UVR
        m_limit = m_limitA | m_limitB | m_limitC;
        m_consum = m_consumA | m_consumB | m_consumC;
    }
}

void jpmic::temp_chk() {
    while(true) {
        wait();

        uint8_t temp = temp_in.read();

        // check temperature warning
        switch(m_regs[0x1B] & 0x07) {
            case 0x01:
                m_twarn = (temp >= 85);
                break;
            case 0x02:
                m_twarn = (temp >= 95);
                break;
            case 0x03:
                m_twarn = (temp >= 105);
                break;
            case 0x04:
                m_twarn = (temp >= 115);
                break;
            case 0x05:
                m_twarn = (temp >= 125);
                break;
            case 0x06:
                m_twarn = (temp >= 135);
                break;
            default:
                m_twarn = false;
        }

        // check shutdown temperature
        m_shutdown = (temp >= (105 + (5 * (m_regs[0x2E] & 0x07))));
    }
}

void jpmic::fsm() {
    while (true) {
        wait();

        // run the PMIC state machine
        switch(m_state) {
            case pmic_state_t::P0:
                if ((m_v18 >= m_cfg.v18_setting) && (m_v10 >= m_cfg.v10_setting) && (bulk_in->read() >= m_cfg.bulk_pg_thresh)) {
                    m_state = pmic_state_t::P2_B;
                }
                else if (bulk_in->read() >= m_cfg.bulk_pg_thresh) {
                    pwrgd_inout.write(false);
                    ldo_ramp_en.write(true);
                }
                else {
                    m_regs = m_regs_backup;
                }

                break;
            case pmic_state_t::P1:
                if (vren_in.posedge() && (m_regs[0x1A] & 0x10)) {
                    // turn back on from Quiescent state
                    m_state = pmic_state_t::RAMPUP;
                }

                break;
            case pmic_state_t::P2_B: {
                // VR_EN must be written and BULK must be valid to ramp rails (initial start, after a fault, etc)
                if (m_vren || (vren_in.posedge() && !(m_regs[0x32] & 0x20))) {
                    m_state = pmic_state_t::RAMPUP;
                }

                break;
            }
            case pmic_state_t::RAMPUP: {
                if (railA_pwrgd.read() && railB_pwrgd.read() && railC_pwrgd.read()) {
                    // go to RUN state
                    pwrgd_inout.write(true);
                    m_regs[0x2F] |= 0x58;
                    m_state = pmic_state_t::P3;
                }
                else if (!railA_zero.read() && !railB_zero.read() && !railC_zero.read()) {
                    // enable all rails
                    rail_en.write(true);
                }

                m_vren = ((m_vren) ? false : m_vren);
                break;
            }
            case pmic_state_t::P3: {
                if (bulk_in->read() < m_cfg.bulk_pg_thresh) {
                    // soft reset (ramp down nicely)
                    ldo_ramp_en.write(false);
                    m_state = pmic_state_t::RAMPDN;
                }
                else if ((m_vrdis && (((m_regs[0x2F] & 0x04) && !(m_regs[0x1A] & 0x10)) ||
                                      ((m_regs[0x2F] & 0x04) && (m_regs[0x1A] & 0x10)))) ||
                         (vren_in.negedge() && ((!(m_regs[0x32] & 0x20) && !(m_regs[0x1A] & 0x10)) ||
                                                 (!(m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)))) ||
                         (pwrgd_inout.negedge() && (m_regs[0x32] & 0x20))) {
                    // ramp down nicely
                    if (!m_vrdis) {
                        // drive PWRGD low if a pin toggles
                        pwrgd_inout.write(false);
                    }
                    m_state = pmic_state_t::RAMPDN;
                }
                else if ((m_regs[0x2F] & 0x4C) != 0x4C) {
                    for(auto &rail : *rails) {
                        if (!(m_regs[0x2F] & 0x40)) {
                            rail_en.write(false);
                        }
                        else if (!(m_regs[0x2F] & 0x10)) {
                            rail_en.write(false);
                        }
                        else if (!(m_regs[0x2F] & 0x08)) {
                            rail_en.write(false);
                        }
                    }
                }
                else {
                    // check the rails for faults
                    if (m_ovr | m_uvr | m_bulk_ovr | m_bulk_uvr) {
                        // drive PWRGD low if a pin toggles
                        pwrgd_inout.write(false);
                        m_state = pmic_state_t::RAMPDN;
                    }
                }
    
                break;
            }
            case pmic_state_t::RAMPDN: {
                // disable all rails
                if(railA_pwrgd.read() && railB_pwrgd.read() && railC_pwrgd.read()) {
                    rail_en.write(false);
                    m_regs[0x2F] &= 0x07;
                }
                else if(!railA_zero.read() && !railB_zero.read() && !railC_zero.read()) {
                    // reset rail power good
                    if (bulk_in->read() < m_cfg.bulk_pg_thresh) {
                        m_state = pmic_state_t::P0;
                    }
                    else if ((!(m_regs[0x32] & 0x20) && !(m_regs[0x1A] & 0x10)) ||
                              ((m_regs[0x2F] & 0x04) && !(m_regs[0x1A] & 0x10)) ||
                               (m_regs[0x32] & 0x20)) {
                        // P3 -> P2_A1
                        m_state = pmic_state_t::P2_A1;
                    }
                    else if ((!(m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)) ||
                             ((m_regs[0x2F] & 0x04) && (m_regs[0x1A] & 0x10))) {
                        // P3 -> P1
                        ldo_ramp_en.write(false);
                        m_state = pmic_state_t::P1;
                    }
                    else {
                        // internal VR Disable Event (fault)
                        // P3 -> P2_A2
                        m_state = pmic_state_t::P2_A2;
                    }

                    m_vrdis = ((m_vrdis) ? false : m_vrdis);
                }

                break;
            }
            case pmic_state_t::P2_A1: {
                // if we have lost power, go OFFLINE; otherwise go to CONFIG
                if (bulk_in->read() < m_cfg.bulk_pg_thresh) {
                    ldo_ramp_en.write(false);
                    m_state = pmic_state_t::RAMPDN;
                }
                else if (vren_in.posedge() &&
                        !(m_regs[0x32] & 0x20) &&
                        !(m_regs[0x1A] & 0x10)) {
                    //pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }
                else if (m_vren && 
                        ((!(m_regs[0x2F] & 0x04) && (m_regs[0x32] & 0x20)) ||
                        ((m_regs[0x2F] & 0x04) && !(m_regs[0x1A] & 0x10)) ||
                        ((m_regs[0x2F] & 0x04) && (m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)))) {
                    //pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }
                else {
                    if (m_bulk_ovr | m_bulk_uvr) {
                        m_state = pmic_state_t::P2_A2;
                    }
                }

                break;
            }
            case pmic_state_t::P2_A2: {
                // if we have lost power, go OFFLINE; otherwise go to CONFIG
                if (bulk_in->read() < m_cfg.bulk_pg_thresh) {
                    ldo_ramp_en.write(false);
                    m_state = pmic_state_t::RAMPDN;
                }
                else if ((m_vren || vren_in.posedge()) && !(m_regs[0x32] & 0x20)) {
                    // pin or VR_EN written when not allowed
                    pwrgd_inout.write(false);
                }
                else if (vren_in.posedge() &&
                        (((m_regs[0x2F] & 0x04) && !(m_regs[0x32] & 0x20) && !(m_regs[0x1A] & 0x10)) ||
                        ((m_regs[0x2F] & 0x04) && !(m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)))) {
                    pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }
                else if (m_vren && (((m_regs[0x2F] & 0x04) && !(m_regs[0x1A] & 0x10)) ||
                        ((m_regs[0x2F] & 0x04) && !(m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)) ||
                        ((m_regs[0x2F] & 0x04) && (m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)))) {
                    pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }

                break;
            }
            default:
                m_state = m_state;
        }
    }
}

void jpmic::ldo_ramp() {
    while (true) {
        wait();

        // run the PMIC state machine
        if (ldo_ramp_en.posedge()) {
            while((m_v18 < m_cfg.v18_setting) || (m_v10 < m_cfg.v10_setting)) {
                m_v18 = (((m_v18+50) > m_cfg.v18_setting) ? m_cfg.v18_setting : m_v18+50);
                   
                if (m_v18 >= m_cfg.v18_setting) {
                    m_v10 = (((m_v10+50) > m_cfg.v10_setting) ? m_cfg.v10_setting : m_v10+50);
                }
    
                v1p8_out.write(m_v18);
                v1p0_out.write(m_v10);
            }
        }
        else if (ldo_ramp_en.negedge()) {
            while ((m_v18 > 0) || (m_v10 > 0)) {
                m_v18 = (((int)(m_v18-50) < 0) ? 0 : m_v18-50);
                m_v10 = (((int)(m_v10-50) < 0) ? 0 : m_v10-50);

                v1p8_out.write(m_v18);
                v1p0_out.write(m_v10);
            }
        }
    }
}
