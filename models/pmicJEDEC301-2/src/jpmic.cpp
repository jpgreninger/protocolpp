#include "jpmic.h"

// Reset the device (cold, hard, soft)
void jpmic::regs() {
    while(true) {
        wait();

        bool wrb = wrb_in.read();
        uint8_t addr = addr_in.read();
        uint8_t data = data_in.read();

        switch(addr) {
            case 0x0C:
                if (wrb) {
                    data_out.write(0);
                }
                else {
                    m_regs[0x0C] = railA_out.read();
                    data_out.write(m_regs[0x0C]);
                }
                break;
            case 0x0E:
                if (wrb) {
                    data_out.write(0);
                }
                else {
                    m_regs[0x0C] = railA_out.read();
                    data_out.write(m_regs[0x0E]);
                }
                break;
            case 0x0F:
                if (wrb) {
                    data_out.write(0);
                }
                else {
                    m_regs[0x0C] = railA_out.read();
                    data_out.write(m_regs[0x0F]);
                }
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
            case 0x30: {
                m_regs[addr] = data;
                uint32_t railVolt = 0;

                if (data & 0x80) {
                    switch(data & 0x78) {
                        case 0:
                            railVolt = railA_out.read();
                            m_regs[0x31] = ((railVolt >= 3875) ? 0xFF : railVolt/15);
                        case 2:
                            railVolt = railB_out.read();
                            m_regs[0x31] = ((railVolt >= 3875) ? 0xFF : railVolt/15);
                        case 3:
                            railVolt = railC_out.read();
                            m_regs[0x31] = ((railVolt >= 3875) ? 0xFF : railVolt/15);
                        case 5:
                            railVolt = bulk_in->read();
                            m_regs[0x31] = ((railVolt >= 17850) ? 0xFF : railVolt/70);
                        case 8:
                            m_regs[0x31] = ((m_v18 >= 3875) ? 0xFF : m_v18/15);
                        case 9:
                            m_regs[0x31] = ((m_v10 >= 3875) ? 0xFF : m_v10/15);
                        default:
                            m_regs[0x31] = 0;
                    }

                    if (wrb) {
                        data_out.write(0);
                    }
                    else {
                        data_out.write(m_regs[0x31]);
                    }
                }
                break;
            }
            case 0x32: {
                if((data & 0x80) && ((m_regs[addr] & 0x80) == 0)) {
                    m_vren = true;
                }
                else if(((data & 0x80) == 0) && (m_regs[addr] & 0x80)) {
                    m_vrdis = true;
                }

                m_regs[addr] = data;
                break;
            }
            default:
                if (wrb) {
                    m_regs[addr] = data;
                }
                else {
                    data_out.write(m_regs[addr]);
                }
        }
    }
}

void jpmic::run() {
    while (true) {
        wait();

        // run the PMIC state machine
        switch(m_state) {
            case pmic_state_t::P0:
                if ((m_v18 >= m_cfg.v18_setting) && (m_v10 >= m_cfg.v10_setting) && (bulk_in->read() >= m_cfg.bulk_pg_thresh)) {
                    pwrgd_inout.write(true);
                    m_state = pmic_state_t::P2_B;
                }
                else if (bulk_in->read() >= m_cfg.bulk_pg_thresh) {
                    pwrgd_inout.write(false);
                    ldo_ramp_en.write(true);
                }

                break;
            case pmic_state_t::P1:
                if (vren_in.posedge() && ((m_regs[0x1A] & 0x10) == 0x10)) {
                    // turn back on from Quiescent state
                    m_state = pmic_state_t::RAMPUP;
                }

                break;
            case pmic_state_t::P2_B: {
                // VR_EN must be written and BULK must be valid to ramp rails (initial start, after a fault, etc)
                if (m_vren || (vren_in.posedge() && ((m_regs[0x32] & 0x20) == 0))) {
                    m_state = pmic_state_t::RAMPUP;
                    break;
                }
            }
            case pmic_state_t::RAMPUP: {
                if (railA_pwrgd.read() && railB_pwrgd.read() && railC_pwrgd.read()) {
                    // go to RUN state
                    pwrgd_inout.write(true);
                    m_vren = ((m_vren) ? false : m_vren);
                    m_regs[0x2F] |= 0x4C;
                    m_state = pmic_state_t::P3;
                }
                else if (!railA_zero.read() && !railB_zero.read() && !railC_zero.read()) {
                    // enable all rails
                    rail_en.write(true);
                }
                break;
            }
            case pmic_state_t::P3: {
                if (bulk_in->read() < m_cfg.bulk_pg_thresh) {
                    // soft reset (ramp down nicely)
                    m_state = pmic_state_t::P0;
                }
                else if (m_vrdis ||
                         vren_in.negedge() ||
                        (pwrgd_inout.negedge() && ((m_regs[0x32] & 0x20) == 0x20))) {
                    // ramp down nicely
                    if (!m_vrdis) {
                        // drive PWRGD low if a pin toggles
                        pwrgd_inout.write(false);
                    }
                    m_state = pmic_state_t::RAMPDN;
                }
                else if ((m_regs[0x2F] & 0x4C) != 0x4C) {
                    for(auto &rail : *rails) {
                        if ((m_regs[0x2F] & 0x40) == 0) {
                            rail_en.write(false);
                        }
                        else if ((m_regs[0x2F] & 0x08) == 0) {
                            rail_en.write(false);
                        }
                        else if ((m_regs[0x2F] & 0x04) == 0) {
                            rail_en.write(false);
                        }
                    }
                }
                else {
                    // check the rails for faults
                    m_error = false;

//                    for(auto &rail : *rails) {
//                        if (rail->voltage() > m_cfg.bulk_max_volt) {
//                            error = true;
//                        }
//                        else if (rail->voltage() < m_cfg.bulk_pg_thresh) {
//                            error = true;
//                        }
//
//                        if (error) {
//                            // drive PWRGD low if a pin toggles
//                            m_state = pmic_state_t::RAMPDN;
//
//                        }
//                    }
                }
    
                break;
            }
            case pmic_state_t::RAMPDN: {
                // disable all rails
                if(railA_pwrgd.read() && railA_pwrgd.read() && railA_pwrgd.read()) {
                    if ((vren_in.negedge() && ((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x1A] & 0x10) == 0x10)) ||
                        (vren_in.negedge() && ((m_regs[0x32] & 0x20) == 0) && ((m_regs[0x1A] & 0x10) == 0)) ||
                        (pwrgd_inout.negedge() && ((m_regs[0x32] & 0x20) == 0x20)) ||
                        m_error) {
                       // drive PWRGD low when required
                        pwrgd_inout.write(false);
                    }

                    rail_en.write(false);
                    m_regs[0x2F] &= 0xB3;
                }
                else if(!railA_zero.read() && !railA_zero.read() && !railA_zero.read()) {
                    // reset rail power good
                    if ((vren_in.negedge() && (((m_regs[0x32] & 0x20) == 0) && ((m_regs[0x1A] & 0x10) == 0))) ||
                        (m_vrdis && (((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x1A] & 0x10) == 0))) ||
                        (pwrgd_inout.negedge() && ((m_regs[0x32] & 0x20) == 0x20))) {
                        // P3 -> P2_A1
                        m_state = pmic_state_t::P2_A1;
                    }
                    else if ((m_vrdis && ((m_regs[0x32] & 0x20) == 0) && ((m_regs[0x1A] & 0x10) == 0x10)) ||
                             (vren_in.negedge() && ((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x1A] & 0x10) == 0x10))) {
                        // P3 -> P1
                        ldo_ramp_en.write(false);
                        m_state = pmic_state_t::P1;
                    }
                    else {
                        // internal VR Disable Event (fault)
                        pwrgd_inout.write(false);
                        m_state = pmic_state_t::P2_A2;
                    }

                    m_vrdis = ((m_vrdis) ? false : m_vrdis);
                    m_error = false;
                }

                break;
            }
            case pmic_state_t::P2_A1: {
                // if we have lost power, go OFFLINE; otherwise go to CONFIG
                if (bulk_in->read() < m_cfg.bulk_pg_thresh) {
                    m_state = pmic_state_t::P0;
                }
                else if (vren_in.read() &&
                        ((m_regs[0x32] & 0x20) == 0) &&
                        ((m_regs[0x1A] & 0x10) == 0)) {
                    //pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }
                else if (m_vren && ((((m_regs[0x2F] & 0x02) == 0) && ((m_regs[0x32] & 0x20) == 0x20)) ||
                        (((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x1A] & 0x10) == 0x0)) ||
                        (((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x32] & 0x20) == 0x20) && ((m_regs[0x1A] & 0x10) == 0x10)))) {
                    //pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }
                else {
                    // check the rails for faults
                    m_error = false;

//                    for(auto &rail : *rails) {
//                        if (rail->voltage() > m_cfg.bulk_max_volt) {
//                            error = true;
//                        }
//                        else if (rail->voltage() < m_cfg.bulk_pg_thresh) {
//                            error = true;
//                        }
//
//                        if (error) {
//                            m_state = pmic_state_t::P2_A2;
//                        }
//                    }
                }

                break;
            }
            case pmic_state_t::P2_A2: {
                // if we have lost power, go OFFLINE; otherwise go to CONFIG
                if (bulk_in->read() < m_cfg.bulk_pg_thresh) {
                    m_state = pmic_state_t::P0;
                }
                else if (((m_regs[0x32] & 0x20) == 0) && (m_vren || vren_in.posedge())) {
                    // pin or VR_EN written when not allowed
                    pwrgd_inout.write(false);
                }
                else if (vren_in.posedge() && ((((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x32] & 0x20) == 0) && ((m_regs[0x1A] & 0x10) == 0)) ||
                        (((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x32] & 0x20) == 0) && ((m_regs[0x1A] & 0x10) == 0x10)))) {
                    pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }
                else if (m_vren && ((((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x1A] & 0x10) == 0)) ||
                        (((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x32] & 0x20) == 0) && ((m_regs[0x1A] & 0x10) == 0x10)) ||
                        (((m_regs[0x2F] & 0x02) == 0x02) && ((m_regs[0x32] & 0x20) == 0x20) && ((m_regs[0x1A] & 0x10) == 0x10)))) {
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
                m_v18 = (((m_v18-50) > 0) ? m_v18-50 : 0);
                m_v10 = (((m_v10-50) > 0) ? m_v10-50 : 0);

                v1p8_out.write(m_v18);
                v1p0_out.write(m_v10);
            }
        }
    }
}
