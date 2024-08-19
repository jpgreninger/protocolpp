#include "jpmic.h"

// Reset the device (cold, hard, soft)
void jpmic::regs() {

    while(true) {
        wait();

        bool wrb = wrb_in.read();
        uint8_t addr = addr_in.read();
        uint8_t data = data_in.read();
        uint32_t railVolt = 0;

        // burn memory and new password
        if (burn_memory) {
            wait(200, SC_MS);
            m_regs[0x39] = 0x5A;
            burn_memory = false;
        }

        if ((secured &&
           (((addr >= 0x15) && (addr <= 0x2F)) ||
           ((addr >= 0x40) && (addr <= 0x6F)))) || 
            (r32_locked && (addr == 0x32))) {
            // block writes to registers if secured
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
                case 0x10:
                    m_regs[0x08] &= ~data;
                    break;
                case 0x11:
                    m_regs[0x09] &= ~data;
                    break;
                case 0x12:
                    m_regs[0x0A] &= ~data;
                    break;
                case 0x13:
                    m_regs[0x0B] &= ~data;
                    break;
                case 0x14:
                    if (data & 0x01) {
                        m_regs[0x08] = 0;
                        m_regs[0x0A] = 0;
                        m_regs[0x0B] = 0;
                        m_regs[0x0C] = 0;
                        m_regs[0x0D] = 0;
                    }
                    else {
                        m_regs[0x0C] &= ~(data & 0x04);
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
                    if ((m_regs[0x2F] & 0x04) == 0x04) {
                        if (((m_regs[0x2F] & 0x40) == 0x40) && ((data & 0x40) == 0x00)) {
                            // turn off railA
                            railA_ramp = false;
                        }
                        else if (((m_regs[0x2F] & 0x40) == 0x00) && ((data & 0x40) == 0x40)) {
                            // turn on railA
                            railA_ramp = true; 
                        }
    
                        if (((m_regs[0x2F] & 0x10) == 0x10) && ((data & 0x10) == 0x00)) {
                            // turn off railB
                            railB_ramp = false;
                        }
                        else if (((m_regs[0x2F] & 0x10) == 0x00) && ((data & 0x10) == 0x10)) {
                            // turn on railB
                            railB_ramp = true; 
                        }
    
                        if (((m_regs[0x2F] & 0x08) == 0x08) && ((data & 0x08) == 0x00)) {
                            // turn off railC
                            railC_ramp = false;
                        }
                        else if (((m_regs[0x2F] & 0x08) == 0x00) && ((data & 0x08) == 0x08)) {
                            // turn on railC
                            railC_ramp = true; 
                        }
                    }

                    // bits 7 and 5 are reserved, only write SECURE_MODE before VR_EN=1
                    m_regs[0x2F] = ((m_regs[0x32] & 0x80) ? (data | (m_regs[0x2F] & 0x04)) : data);
                    break;
                }
                case 0x30: {
                    // bit 2 reserved
                    m_regs[addr] = data;

                    if (data & 0x80) {
                        switch(data & 0x78) {
                            case 0:
                                // ADC select for SWA voltage
                                cmd_in.write(jdac::dac_t::VOLTAGE);
                                break;
                            case 2:
                                // ADC select for SWB voltage
                                cmd_in.write(jdac::dac_t::VOLTAGE | 0x10);
                                break;
                            case 3:
                                // ADC select for SWC voltage
                                cmd_in.write(jdac::dac_t::VOLTAGE | 0x20);
                                break;
                            case 5:
                                // ADC select for BULK voltage
                                cmd_in.write(jdac::dac_t::BULK);
                                break;
                            case 8:
                                // ADC select for LDO 1.8v
                                cmd_in.write(jdac::dac_t::LDO18);
                                break;
                            case 9:
                                // ADC select for LDO 1.0v
                                cmd_in.write(jdac::dac_t::LDO10);
                                break;
                            default:
                                m_regs[0x31] = m_regs[0x31];
                        }
                    }
                    else {
                        m_regs[0x31] = 0;
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

                    // cannot write bit 6 (read-only), 2:0 reserved
                    m_regs[addr] = (data & 0xB8);
                    break;
                }
                case 0x33:
                case 0x34:
                    // RO register
                    break;
                case 0x35:
                    // error injection
                    if ((m_state == pmic_state_t::P2_B) || (m_state == pmic_state_t::P3)) {
//                        switch(data & 0x77) {
//                            case 0x02:
//                                shutdn_inj = true;
//                                break;
//                            case 0x03:
//                                hi_temp_warn_inj = true;
//                                break;
//                            case 0x04:
//                                ldo_v18_pg_inj = true;
//                                break;
//                            case 0x05:
//                                hi_consump_inj = true;
//                                break;
//                            case 0x07:
//                                curr_limit_inj = true;
//                                break;
//                            case 0x10:
//                                swa_inj = true;
//                                break;
//                            case 0x30:
//                                swb_inj = true;
//                                break;
//                            case 0x40:
//                                swc_inj = true;
//                                break;
//                            case 0x50:
//                                bulk_inj = true;
//                                break;
//                            default:
//                                shutdn_inj = false;
//                                hi_temp_warn_inj = false;
//                                ldo_v18_pg_inj = false;
//                                hi_consump_inj = false;
//                                curr_limit_inj = false;
//                                swa_inj = false;
//                                swb_inj = false;
//                                swc_inj = false;
//                                bulk_inj = false;
//                        }
    
                        shutdn_inj       = (((data & 0x77) == 0x02) ? true : false);
                        hi_temp_warn_inj = (((data & 0x77) == 0x03) ? true : false);
                        ldo_v18_pg_inj   = (((data & 0x77) == 0x04) ? true : false);
                        hi_consump_inj   = (((data & 0x77) == 0x05) ? true : false);
                        curr_limit_inj   = (((data & 0x77) == 0x07) ? true : false);
                        swa_inj          = (((data & 0x77) == 0x10) ? true : false);
                        swb_inj          = (((data & 0x77) == 0x30) ? true : false);
                        swc_inj          = (((data & 0x77) == 0x40) ? true : false);
                        bulk_inj         = (((data & 0x77) == 0x50) ? true : false);
                        err_inject   = (((data & 0x80) && ((data & 0x77) != 0)) ? true : false);
                        ovrb_uvr_inj = ((data & 0x08) ? true : false);
                        m_regs[addr] = data;
                    }
                    break;
                case 0x37:
                    if (unlocked) {
                        passwd[0] = m_regs[addr];
                    }
                    else {
                        m_regs[addr] = data;
                        passwd0_wr = ((passwd[0] == m_regs[addr]) ? true : false);
                    }
                    break;
                case 0x38:
                    if (unlocked) {
                        passwd[1] = m_regs[addr];
                    }
                    else {
                        m_regs[addr] = data;
                        passwd1_wr = ((passwd[1] == m_regs[addr]) ? true : false);
                    }
                    break;
                case 0x39:
                    switch(data) {
                        case 0x00:
                            if (unlocked) {
                                unlocked   = false;
                                passwd0_wr = false;
                                passwd1_wr = false;
                            }
                            break;
                        case 0x40:
                            unlocked = !unlocked && passwd0_wr && passwd1_wr;
                            break;
                        case 0x74:
                            if (unlocked) {
                                m_regs[0x04] = 0;
                                m_regs[0x05] = 0;
                                m_regs[0x06] = 0;
                                m_regs[0x07] = 0;
                            }
                            break;
                        case 0x80:
                        case 0x81:
                        case 0x82:
                        case 0x85:
                            if (unlocked) {
                                burn_memory = true;
                            }
                            break;
                        default:
                            unlocked = false;
                            burn_memory = false;
                    }
                case 0x3B:
                case 0x3C:
                case 0x3D:
                    // RO register
                    break;
                case 0x40:
                case 0x41:
                case 0x42:
                case 0x43:
                case 0x44:
                case 0x45:
                case 0x46:
                case 0x47:
                case 0x48:
                case 0x49:
                case 0x4A:
                case 0x4B:
                case 0x4C:
                case 0x4D:
                case 0x4E:
                case 0x4F:
                case 0x50:
                case 0x51:
                case 0x52:
                case 0x53:
                case 0x54:
                case 0x55:
                case 0x56:
                case 0x57:
                case 0x58:
                case 0x59:
                case 0x5A:
                case 0x5B:
                case 0x5C:
                case 0x5D:
                case 0x5E:
                case 0x5F:
                case 0x60:
                case 0x61:
                case 0x62:
                case 0x63:
                case 0x64:
                case 0x65:
                case 0x66:
                case 0x67:
                case 0x68:
                case 0x69:
                case 0x6A:
                case 0x6B:
                case 0x6C:
                case 0x6D:
                case 0x6E:
                case 0x6F:
                    if (unlocked) {
                        m_regs[addr] = data;
                    }
                    break;
                default:
                    m_regs[addr] = data;
            }
        }
        else {
            switch(addr) {
                case 0x04:
                case 0x05:
                case 0x06:
                case 0x07:
                case 0x08:
                case 0x09:
                case 0x0A:
                case 0x0B:
                    data_out.write(m_regs[addr]);
                    break;
                case 0x0C:
                    if (m_regs[0x1B] & 0x40) {
                        // write the SWA power measurement
                        cmd_in.write(0x06);
                        m_regs[addr] = dac_data_out.read();
                    }
                    else {
                        // write the SWA current measurement
                        cmd_in.write(0x04);
                        m_regs[addr] = dac_data_out.read();
                    }
                    data_out.write(m_regs[addr]);
                    break;
                case 0x0E:
                    if (m_regs[0x1B] & 0x40) {
                        // write the SWB power measurement
                        cmd_in.write(0x16);
                        m_regs[addr] = dac_data_out.read();
                    }
                    else {
                        // write the SWB current measurement
                        cmd_in.write(0x14);
                        m_regs[addr] = dac_data_out.read();
                    }
                    data_out.write(m_regs[addr]);
                    break;
                case 0x0F:
                    if (m_regs[0x1B] & 0x40) {
                        // write the SWC power measurement
                        cmd_in.write(0x26);
                        m_regs[addr] = dac_data_out.read();
                    }
                    else {
                        // write the SWC current measurement
                        cmd_in.write(0x24);
                        m_regs[addr] = dac_data_out.read();
                    }
                    data_out.write(m_regs[addr]);
                    break;
                case 0x15:
                case 0x16:
                case 0x17:
                case 0x18:
                case 0x19:
                case 0x1A:
                case 0x1B:
                case 0x1C:
                case 0x1D:
                case 0x1E:
                case 0x1F:
                case 0x20:
                case 0x21:
                case 0x22:
                case 0x23:
                case 0x24:
                case 0x25:
                case 0x26:
                case 0x27:
                case 0x28:
                case 0x29:
                case 0x2A:
                case 0x2B:
                case 0x2C:
                case 0x2D:
                case 0x2E:
                case 0x2F:
                case 0x30:
                    data_out.write(m_regs[addr]);
                    break;
                case 0x31:
                    if (m_regs[0x30] & 0x80) {
                        switch(m_regs[0x30] & 0x78) {
                            case 0:
                            case 2:
                            case 3:
                            case 5:
                            case 8:
                            case 9:
                                m_regs[0x31] = dac_data_out.read();
                                break;
                            default:
                                m_regs[0x31] = 0;
                        }
                    }
                    else {
                        m_regs[0x31] = 0;
                    }
                    data_out.write(m_regs[addr]);
                    break;
                case 0x32:
                    data_out.write(m_regs[addr]);
                    break;
                case 0x33:
                    // sample the temperature
                    cmd_in.write(0x07);
                    m_regs[addr] = (dac_data_out.read() << 5);
                    data_out.write(m_regs[addr]);
                    break;
                case 0x34:
                case 0x35:
                    data_out.write(m_regs[addr]);
                    break;
                case 0x37:
                case 0x38:
                    // WO registers
                    data_out.write(0);
                    break;
                case 0x39:
                case 0x3A:
                case 0x3B:
                case 0x3C:
                case 0x3D:
                    data_out.write(m_regs[addr]);
                    break;
                default:
                    if (unlocked) {
                        data_out.write(m_regs[addr]);
                    }
                    else {
                        data_out.write(0);
                    }
            }
        }
    }
}

void jpmic::volt_chk() {

    // initial values
    bool m_ovrA=false;
    bool m_ovrB=false;
    bool m_ovrC=false;

    bool m_uvrA=false;
    bool m_uvrB=false;
    bool m_uvrC=false;

    bool m_bovr=false;
    bool m_buvr=false;

    bool swa_pg=false;
    bool swb_pg=false;
    bool swc_pg=false;
    bool bul_pg=false;

    int tOutput_OV_VR_Disable_A_cntr=0;
    int tOutput_OV_VR_Disable_B_cntr=0;
    int tOutput_OV_VR_Disable_C_cntr=0;

    int tOutput_UV_VR_Disable_A_cntr=0;
    int tOutput_UV_VR_Disable_B_cntr=0;
    int tOutput_UV_VR_Disable_C_cntr=0;
    int tOutput_UV_VR_Disable_Bulk_cntr=0;

    bool tOutput_OV_VR_Disable_A_trigger=false;
    bool tOutput_OV_VR_Disable_B_trigger=false;
    bool tOutput_OV_VR_Disable_C_trigger=false;

    bool tOutput_UV_VR_Disable_A_trigger=false;
    bool tOutput_UV_VR_Disable_B_trigger=false;
    bool tOutput_UV_VR_Disable_C_trigger=false;
    bool tOutput_UV_VR_Disable_Bulk_trigger=false;

    int tInput_OV_GSI_Assertion_cntr=0;
    int tInput_OV_VR_Disable_cntr=0;

    bool tInput_OV_GSI_Assertion_trigger=false;
    bool tInput_OV_VR_Disable_trigger=false;

    while (true) {
        // wait for posedge clock
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
                m_ovrA = ((railA_vout > (railA_setting + (railA_setting * 0.0075))) || (err_inject && !ovrb_uvr_inj && swa_inj));
                break;
            case 0x10:
                m_ovrA = ((railA_vout > (railA_setting + (railA_setting * 0.01))) || (err_inject && !ovrb_uvr_inj && swa_inj));
                break;
            case 0x20:
                m_ovrA = ((railA_vout > (railA_setting + (railA_setting * 0.0125))) || (err_inject && !ovrb_uvr_inj && swa_inj));
                break;
            default:
                m_ovrA = false;
        }

        // SWA UVR
        switch(m_regs[0x22] & 0x0C) {
            case 0x00:
                m_uvrA = ((railA_vout < (railA_setting - (railA_setting * 0.010))) || (err_inject && ovrb_uvr_inj && swa_inj));
                break;
            case 0x04:
                m_uvrA = ((railA_vout < (railA_setting - (railA_setting * 0.0125))) || (err_inject && ovrb_uvr_inj && swa_inj));
                break;
            default:
                m_uvrA = false;
        }

        // SWB OVR
        switch(m_regs[0x26] & 0x30) {
            case 0x00:
                m_ovrB = ((railB_vout > (railB_setting + (railB_setting * 0.0075))) || (err_inject && !ovrb_uvr_inj && swb_inj));
                break;
            case 0x10:
                m_ovrB = ((railA_vout > (railA_setting + (railA_setting * 0.01))) || (err_inject && !ovrb_uvr_inj && swb_inj));
                break;
            case 0x20:
                m_ovrB = ((railA_vout > (railA_setting + (railA_setting * 0.0125))) || (err_inject && !ovrb_uvr_inj && swb_inj));
                break;
            default:
                m_ovrB = false;
        }

        // SWB UVR
        switch(m_regs[0x26] & 0x0C) {
            case 0x00:
                m_uvrB = ((railB_vout < (railB_setting - (railB_setting * 0.010))) || (err_inject && ovrb_uvr_inj && swb_inj));
                break;
            case 0x04:
                m_uvrA = ((railB_vout < (railB_setting - (railB_setting * 0.0125))) || (err_inject && ovrb_uvr_inj && swb_inj));
                break;
            default:
                m_uvrB = false;
        }

        // SWC OVR
        switch(m_regs[0x28] & 0x30) {
            case 0x00:
                m_ovrC = ((railC_vout > (railC_setting + (railC_setting * 0.0075))) || (err_inject && !ovrb_uvr_inj && swc_inj));
                break;
            case 0x10:
                m_ovrC = ((railC_vout > (railC_setting + (railC_setting * 0.01))) || (err_inject && !ovrb_uvr_inj && swc_inj));
                break;
            case 0x20:
                m_ovrC = ((railC_vout > (railC_setting + (railC_setting * 0.0125))) || (err_inject && !ovrb_uvr_inj && swc_inj));
                break;
            default:
                m_ovrC = false;
        }

        // SWC UVR
        switch(m_regs[0x28] & 0x0C) {
            case 0x00:
                m_uvrC = ((railC_vout < (railC_setting - (railC_setting * 0.010))) || (err_inject && ovrb_uvr_inj && swc_inj));
                break;
            case 0x04:
                m_uvrC = ((railC_vout < (railC_setting - (railC_setting * 0.0125))) || (err_inject && ovrb_uvr_inj && swc_inj));
                break;
            default:
                m_uvrC = false;
        }

        // OVR timer for railA
        if (m_ovrA) {
            if (tOutput_OV_VR_Disable_A_cntr < m_cfg.tOutput_OV_VR_Disable) {
                tOutput_OV_VR_Disable_A_cntr++;
            }
            else {
                tOutput_OV_VR_Disable_A_trigger = true;
            }
        }
        else {
            tOutput_OV_VR_Disable_A_cntr=0;
            tOutput_OV_VR_Disable_A_trigger = false;
        }

        // OVR timer for railB
        if (m_ovrB) {
            if (tOutput_OV_VR_Disable_B_cntr < m_cfg.tOutput_OV_VR_Disable) {
                tOutput_OV_VR_Disable_B_cntr++;
            }
            else {
                tOutput_OV_VR_Disable_B_trigger = true;
            }
        }
        else {
            tOutput_OV_VR_Disable_B_cntr=0;
            tOutput_OV_VR_Disable_B_trigger = false;
        }

        // OVR timer for railC
        if (m_ovrC) {
            if (tOutput_OV_VR_Disable_C_cntr < m_cfg.tOutput_OV_VR_Disable) {
                tOutput_OV_VR_Disable_C_cntr++;
            }
            else {
                tOutput_OV_VR_Disable_C_trigger = true;
            }
        }
        else {
            tOutput_OV_VR_Disable_C_cntr=0;
            tOutput_OV_VR_Disable_C_trigger = false;
        }

        // UVR timer for railA
        if (m_uvrA) {
            if (tOutput_UV_VR_Disable_A_cntr < m_cfg.tOutput_UV_VR_Disable) {
                tOutput_UV_VR_Disable_A_cntr++;
            }
            else {
                tOutput_UV_VR_Disable_A_trigger = true;
            }
        }
        else {
            tOutput_UV_VR_Disable_A_cntr=0;
            tOutput_UV_VR_Disable_A_trigger = false;
        }

        // UVR timer for railB
        if (m_uvrB) {
            if (tOutput_UV_VR_Disable_B_cntr < m_cfg.tOutput_UV_VR_Disable) {
                tOutput_UV_VR_Disable_B_cntr++;
            }
            else {
                tOutput_UV_VR_Disable_B_trigger = true;
            }
        }
        else {
            tOutput_UV_VR_Disable_B_cntr=0;
            tOutput_UV_VR_Disable_B_trigger = false;
        }

        // UVR timer for railC
        if (m_uvrC) {
            if (tOutput_UV_VR_Disable_C_cntr < m_cfg.tOutput_UV_VR_Disable) {
                tOutput_UV_VR_Disable_C_cntr++;
            }
            else {
                tOutput_UV_VR_Disable_C_trigger = true;
            }
        }
        else {
            tOutput_UV_VR_Disable_C_cntr=0;
            tOutput_UV_VR_Disable_C_trigger = false;
        }

        // bulk GSI assertion timer
        if (m_bovr) {
            if (tInput_OV_GSI_Assertion_cntr < m_cfg.tInput_OV_GSI_Assertion) {
                tInput_OV_GSI_Assertion_cntr++;
            }
            else {
                tInput_OV_GSI_Assertion_trigger = true;
            }
        }
        else {
            tInput_OV_GSI_Assertion_cntr=0;
            tInput_OV_GSI_Assertion_trigger = false;
        }

        // bulk OVR assertion timer
        if (m_bovr) {
            if (tInput_OV_VR_Disable_cntr < m_cfg.tInput_OV_VR_Disable) {
                tInput_OV_VR_Disable_cntr++;
            }
            else {
                tInput_OV_VR_Disable_trigger = true;
            }
        }
        else {
            tInput_OV_VR_Disable_cntr=0;
            tInput_OV_VR_Disable_trigger = false;
        }

        // bulk UVR assertion timer
        if (m_buvr) {
            if (tOutput_UV_VR_Disable_Bulk_cntr < m_cfg.tOutput_UV_VR_Disable) {
                tOutput_UV_VR_Disable_Bulk_cntr++;
            }
            else {
                tOutput_UV_VR_Disable_Bulk_trigger = true;
            }
        }
        else {
            tOutput_UV_VR_Disable_Bulk_cntr=0;
            tOutput_UV_VR_Disable_Bulk_trigger = false;
        }

        // rail OVR/UVR
        m_ovr = ((m_ovrA && tOutput_OV_VR_Disable_A_trigger) ||
                 (m_ovrB && tOutput_OV_VR_Disable_B_trigger) ||
                 (m_ovrC && tOutput_OV_VR_Disable_C_trigger));

        m_uvr = ((m_uvrA && tOutput_UV_VR_Disable_A_trigger && !railA_fault_mask) ||
                 (m_uvrB && tOutput_UV_VR_Disable_B_trigger && !railB_fault_mask) ||
                 (m_uvrC && tOutput_UV_VR_Disable_C_trigger && !railC_fault_mask));

        // bulk input OVR
        m_bovr = ((bulk_in_read > m_cfg.bulk_max_volt) || (err_inject && !ovrb_uvr_inj && bulk_inj));

        // bulk input UVR
        m_buvr = ((bulk_in_read < m_cfg.bulk_min_volt) || (err_inject && ovrb_uvr_inj && bulk_inj));

        // bulk input OVR/UVR
        m_bulk_ovr = (tInput_OV_VR_Disable_trigger && m_bovr);
        m_bulk_uvr = (tOutput_UV_VR_Disable_Bulk_trigger && m_buvr);

        // bulk input GSI_n
        m_bulk_gsi = (tInput_OV_GSI_Assertion_trigger && m_bovr);

        // rail power good
        swa_pg = !m_ovrA && !m_uvrA;
        swb_pg = !m_ovrB && !m_uvrB;
        swc_pg = !m_ovrC && !m_uvrC;
        bul_pg = !m_bovr && !m_buvr;

        // error log
        m_errlog = ((m_ovr || m_uvr) ? 0x02 : ((m_shutdown) ? 0x03 : ((m_bulk_ovr) ? 0x04 : 0x00)));
        m_errcnt += ((m_errlog != 0) ? 1 : 0);

        // set error logs except when in error_injection and configuration state
        if (!((m_state == pmic_state_t::P2_B) && err_inject)) {
            m_regs[0x04] = ((m_errcnt << 7) | ((m_ovr | m_uvr) << 6) | (m_bulk_ovr << 5) | (m_shutdown << 4));
            m_regs[0x05] = ((swa_pg << 6) | (swb_pg << 4) | (swc_pg << 3) | m_errlog);
            m_regs[0x06] = ((m_uvrA << 7) | (m_uvrB << 5) | (m_uvrC << 4) | (m_ovrA << 3) | (m_ovrB << 1) | m_ovrC);
        }

        // set SWA, SWB, SWC rails OVR, UVR status bits
        m_regs[0x08] = ((m_shutdown << 6) | (swa_pg << 5) | (swb_pg << 3) | (swc_pg << 2) | bul_pg);
        m_regs[0x0A] = ((m_ovrA << 7) | (m_ovrB << 5) | (m_ovrC << 4));
        m_regs[0x0B] |= ((m_uvrA << 3) | (m_uvrB << 1) | m_uvrC);
    }
}

void jpmic::curr_chk() {
    // initial values
    bool m_limitA=false;
    bool m_limitB=false;
    bool m_limitC=false;
    bool m_consumA=false;
    bool m_consumB=false;
    bool m_consumC=false;
    bool m_v18pg=false;

    int tOutput_Current_Limiter_A_cntr=0;
    int tOutput_Current_Limiter_B_cntr=0;
    int tOutput_Current_Limiter_C_cntr=0;

    bool tOutput_Current_Limiter_A_trigger=false;
    bool tOutput_Current_Limiter_B_trigger=false;
    bool tOutput_Current_Limiter_C_trigger=false;

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

        m_regs[0x0C] = railA_curr;
        m_regs[0x0E] = railB_curr;
        m_regs[0x0F] = railC_curr;

        // SWA current limiter
        m_limitA = ((railA_curr > railA_limit) || (err_inject && curr_limit_inj));

        // SWA current consumption
        m_consumA = ((railA_curr > railA_consump) || (err_inject && hi_consump_inj));

        // SWB current limiter
        m_limitB = ((railB_curr > railB_limit) || (err_inject && curr_limit_inj));

        // SWB current consumption
        m_consumB = ((railB_curr > railB_consump) || (err_inject && hi_consump_inj));

        // SWC current limiter
        m_limitC = ((railC_curr > railC_limit) || (err_inject && curr_limit_inj));

        // SWC current consumption
        m_consumC = ((railC_curr > railC_consump) || (err_inject && hi_consump_inj));

        // current limiter warning timer for railA
        if (m_limitA) {
            if (tOutput_Current_Limiter_A_cntr < m_cfg.tOutput_Current_Limiter) {
                tOutput_Current_Limiter_A_cntr++;
            }
            else {
                tOutput_Current_Limiter_A_trigger = true;
            }
        }
        else {
            tOutput_Current_Limiter_A_cntr=0;
            tOutput_Current_Limiter_A_trigger = false;
        }

        // current limiter warning timer for railB
        if (m_limitB) {
            if (tOutput_Current_Limiter_B_cntr < m_cfg.tOutput_Current_Limiter) {
                tOutput_Current_Limiter_B_cntr++;
            }
            else {
                tOutput_Current_Limiter_B_trigger = true;
            }
        }
        else {
            tOutput_Current_Limiter_B_cntr=0;
            tOutput_Current_Limiter_B_trigger = false;
        }

        // current limiter warning timer for railC
        if (m_limitC) {
            if (tOutput_Current_Limiter_C_cntr < m_cfg.tOutput_Current_Limiter) {
                tOutput_Current_Limiter_C_cntr++;
            }
            else {
                tOutput_Current_Limiter_C_trigger = true;
            }
        }
        else {
            tOutput_Current_Limiter_C_cntr=0;
            tOutput_Current_Limiter_C_trigger = false;
        }

        // rail current limit overage
        m_limit = ((m_limitA && ((m_regs[0x18] & 0x80) == 0) && tOutput_Current_Limiter_A_trigger) ||
                   (m_limitB && ((m_regs[0x18] & 0x20) == 0) && tOutput_Current_Limiter_B_trigger) ||
                   (m_limitC && ((m_regs[0x18] & 0x10) == 0) && tOutput_Current_Limiter_C_trigger));

        // rail current high consumption
        m_consum = ((m_consumA && ((m_regs[0x16] & 0x08) == 0)) ||
                    (m_consumB && ((m_regs[0x16] & 0x02) == 0)) ||
                    (m_consumC && ((m_regs[0x16] & 0x01) == 0)));

        // 1.8v power good
        m_v18pg = ((m_v18 >= m_cfg.v18_setting) || ~(err_inject && ldo_v18_pg_inj));

        // set SWA, SWB, SWC rails OVR, UVR status bits
        m_regs[0x09] = ((m_temp_warning << 7) | (m_v18pg << 5) | (m_consumA << 3) | (m_consumB << 1) | m_consumC);
        m_regs[0x0B] |= ((m_limitA << 7) | (m_limitB << 5) | (m_limitC << 4));
    }
}

void jpmic::temp_chk() {
    // initial values
    bool m_shutdwn=false;
    bool m_twarn=false;

    int tHigh_Temp_Warning_cntr=0;
    int tShut_Down_Temp_cntr=0;

    bool tHigh_Temp_Warning_trigger=false;
    bool tShut_Down_Temp_trigger=false;

    while(true) {
        wait();

        uint8_t temp = temp_in.read();

        // check temperature warning
        switch(m_regs[0x1B] & 0x07) {
            case 0x01:
                m_twarn = ((temp >= 85) || (err_inject && hi_temp_warn_inj));
                break;
            case 0x02:
                m_twarn = ((temp >= 95) || (err_inject && hi_temp_warn_inj));
                break;
            case 0x03:
                m_twarn = ((temp >= 105) || (err_inject && hi_temp_warn_inj));
                break;
            case 0x04:
                m_twarn = ((temp >= 115) || (err_inject && hi_temp_warn_inj));
                break;
            case 0x05:
                m_twarn = ((temp >= 125) || (err_inject && hi_temp_warn_inj));
                break;
            case 0x06:
                m_twarn = ((temp >= 135) || (err_inject && hi_temp_warn_inj));
                break;
            default:
                m_twarn = false;
        }

        // check shutdown temperature
        m_shutdwn = ((temp >= (105 + (5 * (m_regs[0x2E] & 0x07)))) || (err_inject && shutdn_inj));

        // temperature warning timer after 10 us
        if (m_twarn) {
            if (tHigh_Temp_Warning_cntr < m_cfg.tHigh_Temp_Warning) {
                tHigh_Temp_Warning_cntr++;
            }
            else {
                tHigh_Temp_Warning_trigger = true;
            }
        }
        else {
            tHigh_Temp_Warning_cntr=0;
            tHigh_Temp_Warning_trigger = false;
        }

        // temperature shutdown timer after 10 us
        if (m_shutdwn) {
            if (tShut_Down_Temp_cntr < m_cfg.tShut_Down_Temp) {
                tShut_Down_Temp_cntr++;
            }
            else {
                tShut_Down_Temp_trigger = true;
            }
        }
        else {
            tShut_Down_Temp_cntr=0;
            tShut_Down_Temp_trigger = false;
        }

        // temperature triggers
        m_temp_warning = m_twarn && ((m_regs[0x16] & 0x80) == 0) && tHigh_Temp_Warning_trigger;
        m_shutdown = m_shutdwn && tShut_Down_Temp_trigger;
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
                    //pwrgd_inout.write(false);
                    ldo_ramp_en.write(true);
                }
                else {
                    secured = false;
                    r32_locked = false;
                    
                    // default register values from JEDEC301-2-1 spec
                    // reload defaults from vendor region
                    m_regs[0x08] = 0x00;
                    m_regs[0x09] = 0x00;
                    m_regs[0x0A] = 0x00;
                    m_regs[0x0B] = 0x00;
                    m_regs[0x0C] = 0x00;
                    m_regs[0x0D] = 0x00;
                    m_regs[0x0E] = 0x00;
                    m_regs[0x0F] = 0x00;

                    m_regs[0x10] = 0x00;
                    m_regs[0x11] = 0x00;
                    m_regs[0x12] = 0x00;
                    m_regs[0x13] = 0x00;
                    m_regs[0x14] = 0x00;
                    m_regs[0x15] = 0x2C;
                    m_regs[0x16] = 0x20;
                    m_regs[0x17] = 0x00;

                    m_regs[0x20] = m_regs[0x50];
                    m_regs[0x21] = m_regs[0x45];
                    m_regs[0x22] = m_regs[0x46];
                    m_regs[0x23] = m_regs[0x47];
                    m_regs[0x24] = m_regs[0x48];
                    m_regs[0x25] = m_regs[0x49];
                    m_regs[0x26] = m_regs[0x4A];
                    m_regs[0x27] = m_regs[0x4B];

                    m_regs[0x28] = m_regs[0x4C];
                    m_regs[0x29] = m_regs[0x4D];
                    m_regs[0x2A] = m_regs[0x4E];
                    m_regs[0x2B] = m_regs[0x51];
                    m_regs[0x2C] = m_regs[0x5D];
                    m_regs[0x2D] = m_regs[0x5E];
                    m_regs[0x2E] = 0x04;
                    m_regs[0x2F] = 0x02;

                    m_regs[0x30] = 0x00;
                    m_regs[0x31] = 0x00;
                    m_regs[0x32] = 0x00;
                    m_regs[0x33] = 0x00;
                    m_regs[0x34] = 0x0E;
                    m_regs[0x35] = 0x00;
                    m_regs[0x36] = 0x00;
                    m_regs[0x37] = 0x00;

                    m_regs[0x38] = 0x00;
                    m_regs[0x39] = 0x00;
                    m_regs[0x3A] = 0x00;
                    m_regs[0x3B] = 0x00;
                    m_regs[0x3C] = 0x0E;
                    m_regs[0x3D] = 0x00;
                    m_regs[0x3E] = 0x00;
                    m_regs[0x3F] = 0x00;

                    shutdn_inj = false;
                    hi_temp_warn_inj = false;
                    ldo_v18_pg_inj = false;
                    hi_consump_inj = false;
                    curr_limit_inj = false;
                    swa_inj = false;
                    swb_inj = false;
                    swc_inj = false;
                    bulk_inj = false;
                }

                m_stateint = 0x00;
                break;
            case pmic_state_t::P1:
                if (vren_in.posedge() && (m_regs[0x1A] & 0x10)) {
                    // turn back on from Quiescent state
                    ldo_ramp_en.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }

                m_stateint = 0x01;
                break;
            case pmic_state_t::P2_B: {
                // VR_EN must be written or VREN_In must toggle and BULK must be valid to ramp rails (initial start, after a fault, etc)
                if (m_bulk_uvr) {
                    // soft reset (ramp down nicely)
                    m_regs[0x32] &= 0x3F;
                    ldo_ramp_en.write(false);
                    m_state = pmic_state_t::P0;
                }
                else if (m_vren || (vren_in.posedge() && !(m_regs[0x32] & 0x20))) {
                    if (!(m_regs[0x2F] & 0x04)) {
                        // PWRGD low can unlock R32
                        secured = true;
                        r32_locked = true;
                    }
                    
                    if (!err_inject) {
                        m_state = pmic_state_t::RAMPUP;
                    }
                }

                m_stateint = 0x2B;
                break;
            }
            case pmic_state_t::RAMPUP: {
                if (railA_pwrgd.read() && railB_pwrgd.read() && railC_pwrgd.read()) {
                    // go to RUN state
                    //pwrgd_inout.write(true);
                    m_regs[0x2F] |= 0x58;
                    m_state = pmic_state_t::P3;
                }
                else if (!railA_zero.read() && !railB_zero.read() && !railC_zero.read()) {
                    // enable all rails
                    railA_en.write(true);
                    railB_en.write(true);
                    railC_en.write(true);
                }

                m_vren = ((m_vren) ? false : m_vren);
                m_stateint = 0xFF;
                break;
            }
            case pmic_state_t::P3: {
                if (m_bulk_uvr) {
                    // soft reset (ramp down nicely)
                    m_regs[0x32] &= 0x3F;
                    ldo_ramp_en.write(false);
                    m_state = pmic_state_t::RAMPDN;
                }
                else if ((m_vrdis && (((m_regs[0x2F] & 0x04) && !(m_regs[0x1A] & 0x10)) ||
                                      ((m_regs[0x2F] & 0x04) && (m_regs[0x1A] & 0x10)))) ||
                         (vren_in.negedge() && ((!(m_regs[0x32] & 0x20) && !(m_regs[0x1A] & 0x10)) ||
                                                 (!(m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)))) ||
                         (pwrgd_inout.negedge() && (m_regs[0x32] & 0x20))) {
                    // ramp down nicely
                    if (pwrgd_inout.negedge() && (m_regs[0x32] & 0x20)) {
                        // external device forced PWRGD low (exception from R32 note 4)
                        r32_locked = false;
                    }

                    m_regs[0x32] &= 0x3F;
                    m_state = pmic_state_t::RAMPDN;
                }
                else if (m_ovr | m_uvr | m_bulk_ovr) {
                    // check for faults
                    m_regs[0x32] &= 0x3F;
                    //pwrgd_inout.write(false);
                    m_state = pmic_state_t::RAMPDN;
                }
                else if ((m_regs[0x2F] & 0x04) == 0x04) {
                    // turn off individual rails if requested
                    if (((m_regs[0x2F] & 0x40) == 0x00) && !railA_ramp) {
                        // turn off railA
                        railA_en.write(false);
                        railA_fault_mask = true;
                    }
                    else if (((m_regs[0x2F] & 0x40) == 0x40) && railA_ramp) {
                        // turn on railA
                        railA_en.write(true);

                        if (railA_pwrgd.read()) {
                            railA_fault_mask = false;
                        }
                    }

                    if (((m_regs[0x2F] & 0x10) == 0x00) && !railB_ramp) {
                        // turn off railB
                        railB_en.write(false);
                        railB_fault_mask = true;
                    }
                    else if (((m_regs[0x2F] & 0x10) == 0x10) && railB_ramp) {
                        // turn on railB
                        railB_en.write(true);

                        if (railB_pwrgd.read()) {
                            railB_fault_mask = false;
                        }
                    }

                    if (((m_regs[0x2F] & 0x08) == 0x00) && !railC_ramp) {
                        // turn off railC
                        railC_en.write(false);
                        railC_fault_mask = true;
                    }
                    else if (((m_regs[0x2F] & 0x08) == 0x08) && railC_ramp) {
                        // turn on railC
                        railC_en.write(true);

                        if (railB_pwrgd.read()) {
                            railB_fault_mask = false;
                        }
                    }
                }
    
                m_stateint = 0x03;
                break;
            }
            case pmic_state_t::RAMPDN: {
                // disable all rails
                if(railA_pwrgd.read() && railB_pwrgd.read() && railC_pwrgd.read()) {
                    railA_en.write(false);
                    railB_en.write(false);
                    railC_en.write(false);
                    m_regs[0x2F] &= 0x07;
                }
                else if(!railA_zero.read() && !railB_zero.read() && !railC_zero.read()) {
                    // reset rail power good
                    if (m_bulk_uvr) {
                        // P3 -> P0 (LDOs off)
                        m_state = pmic_state_t::P0;
                    }
                    else if ((!(m_regs[0x32] & 0x20) && !(m_regs[0x1A] & 0x10)) ||
                              ((m_regs[0x2F] & 0x04) && !(m_regs[0x1A] & 0x10)) ||
                               (m_regs[0x32] & 0x20)) {
                        // P3 -> P2_A1 (LDOs on)
                        m_state = pmic_state_t::P2_A1;
                    }
                    else if ((!(m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)) ||
                             ((m_regs[0x2F] & 0x04) && (m_regs[0x1A] & 0x10))) {
                        // P3 -> P1 (LDOs on)
                        ldo_ramp_en.write(false);
                        m_state = pmic_state_t::P1;
                    }
                    else {
                        // internal VR Disable Event (fault)
                        // P3 -> P2_A2 (LDOs on)
                        m_state = pmic_state_t::P2_A2;
                    }

                    m_vrdis = ((m_vrdis) ? false : m_vrdis);
                }

                m_stateint = 0xFD;
                break;
            }
            case pmic_state_t::P2_A1: {
                // if we have lost power, go OFFLINE; otherwise go to CONFIG
                if (m_bulk_uvr) {
                    ldo_ramp_en.write(false);
                    m_state = pmic_state_t::P0;
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
                    if (m_vren && secured) {
                        r32_locked = true;
                    }
                    m_state = pmic_state_t::RAMPUP;
                }
                else if (m_bulk_ovr) {
                    m_state = pmic_state_t::P2_A2;
                }

                m_stateint = 0xA1;
                break;
            }
            case pmic_state_t::P2_A2: {
                // if we have lost power, go OFFLINE; otherwise go to CONFIG
                if (m_bulk_uvr) {
                    ldo_ramp_en.write(false);
                    m_state = pmic_state_t::P0;
                }
                //else if ((m_vren || vren_in.posedge()) && !(m_regs[0x32] & 0x20)) {
                    // pin or VR_EN written when not allowed
                //    pwrgd_inout.write(sc_dt::SC_LOGIC_0);
                //}
                else if (vren_in.posedge() &&
                        (((m_regs[0x2F] & 0x04) && !(m_regs[0x32] & 0x20) && !(m_regs[0x1A] & 0x10)) ||
                        ((m_regs[0x2F] & 0x04) && !(m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)))) {
                    //pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }
                else if (m_vren && (((m_regs[0x2F] & 0x04) && !(m_regs[0x1A] & 0x10)) ||
                        ((m_regs[0x2F] & 0x04) && !(m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)) ||
                        ((m_regs[0x2F] & 0x04) && (m_regs[0x32] & 0x20) && (m_regs[0x1A] & 0x10)))) {
                    if (m_vren && secured) {
                        r32_locked = true;
                    }
                    //pwrgd_inout.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }

                m_stateint = 0xA2;
                break;
            }
            default:
                m_state = m_state;
        }

        // control PWRGD pin
        if (m_bulk_uvr | m_bulk_ovr | m_ovr | m_uvr | m_shutdown) {
            pwrgd_inout.write(sc_dt::SC_LOGIC_0);
        }
        else {
            pwrgd_inout.write(sc_dt::SC_LOGIC_Z);
        }

        // control GSI_N pin
        if (((m_regs[0x2F] & 0x03) == 0x01) &&
             (m_bulk_uvr | m_bulk_ovr | m_ovr | m_uvr | m_bulk_ovr |
             m_bulk_uvr | m_consum | m_limit | m_temp_warning | m_shutdown |
             (m_temp_warning && (m_regs[0x16] & 0x80)) | m_limit |
            ((m_vren || vren_in.posedge()) && !(m_regs[0x32] & 0x20)))) {
            gsi_n_out.write(false);
        }
        else {
            gsi_n_out.write(true);
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
