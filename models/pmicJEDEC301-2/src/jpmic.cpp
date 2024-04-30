#include "jpmic.h"

// Reset the device (cold, hard, soft)
void jpmic::regs() {
    uint32_t railVolt=0;

    while(true) {
        wait();

        bool wrb = wrb_in.read();
        uint8_t addr = addr_in.read();
        uint8_t data = data_in.read();

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

                    // bits 7 and 5 are reserved
                    m_regs[0x2F] = data;
                    break;
                }
                case 0x30: {
                    // bit 2 reserved
                    m_regs[addr] = data;

                    if (data & 0x80) {
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

                    // cannot write bit 6 (read-only), 2:0 reserved
                    m_regs[addr] = (data & 0xB8);
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
                    data_out.write(0);
                    break;
                default:
                    data_out.write(m_regs[addr]);
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

        m_uvr = ((m_uvrA && tOutput_UV_VR_Disable_A_trigger) ||
                 (m_uvrB && tOutput_UV_VR_Disable_B_trigger) ||
                 (m_uvrC && tOutput_UV_VR_Disable_C_trigger));

        // bulk input OVR
        m_bovr = (bulk_in_read > m_cfg.bulk_max_volt);

        // bulk input GSI_n
        m_bulk_gsi = (tInput_OV_GSI_Assertion_trigger && m_bovr);
        
        // bulk input UVR
        m_buvr = (bulk_in_read < m_cfg.bulk_min_volt);

        // bulk input OVR/UVR
        m_bulk_ovr = (tInput_OV_VR_Disable_trigger && m_bovr);
        m_bulk_uvr = (tOutput_UV_VR_Disable_Bulk_trigger && m_buvr);
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

        // rail OVR/UVR
        m_limit = ((m_limitA && tOutput_Current_Limiter_A_trigger) ||
                   (m_limitB && tOutput_Current_Limiter_B_trigger) ||
                   (m_limitC && tOutput_Current_Limiter_C_trigger));

        m_consum = m_consumA | m_consumB | m_consumC;
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
        m_shutdwn = (temp >= (105 + (5 * (m_regs[0x2E] & 0x07))));

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
        m_temp_warning = m_twarn && tHigh_Temp_Warning_trigger;
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
                    pwrgd_inout.write(false);
                    ldo_ramp_en.write(true);
                }
                else {
                    secured = false;
                    r32_locked = false;
                    
                    // reload defaults from vendor region
                    m_regs[0x15] = 0x2C;
                    m_regs[0x16] = 0x20;
                    m_regs[0x17] = 0x00;
                    m_regs[0x18] = 0x00;
                    m_regs[0x19] = 0x04;
                    m_regs[0x1A] = 0x00;
                    m_regs[0x1B] = 0x05;
                    m_regs[0x1C] = 0x60;
                    m_regs[0x1D] = 0x00;
                    m_regs[0x1E] = 0x60;
                    m_regs[0x1F] = 0x60;
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
                }

                break;
            case pmic_state_t::P1:
                if (vren_in.posedge() && (m_regs[0x1A] & 0x10)) {
                    // turn back on from Quiescent state
                    ldo_ramp_en.write(true);
                    m_state = pmic_state_t::RAMPUP;
                }

                break;
            case pmic_state_t::P2_B: {
                // VR_EN must be written or VREN_In must toggle and BULK must be valid to ramp rails (initial start, after a fault, etc)
                if (m_vren || (vren_in.posedge() && !(m_regs[0x32] & 0x20))) {
                    if (!(m_regs[0x2F] & 0x04)) {
                        // PWRGD low can unlock R32
                        secured = true;
                        r32_locked = true;
                    }

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
                    railA_en.write(true);
                    railB_en.write(true);
                    railC_en.write(true);
                }

                m_vren = ((m_vren) ? false : m_vren);
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
                    pwrgd_inout.write(false);
                    m_state = pmic_state_t::RAMPDN;
                }
                else if ((m_regs[0x2F] & 0x04) != 0x04) {
                    // turn off individual rails if requested

                    if (((m_regs[0x2F] & 0x40) == 0x00) && !railA_ramp) {
                        // turn off railA
                        railA_en.write(false);
                    }
                    else if (((m_regs[0x2F] & 0x40) == 0x40) && railA_ramp) {
                        // turn on railA
                        railA_en.write(true);
                    }

                    if (((m_regs[0x2F] & 0x10) == 0x00) && !railB_ramp) {
                        // turn off railB
                        railB_en.write(false);
                    }
                    else if (((m_regs[0x2F] & 0x10) == 0x10) && railB_ramp) {
                        // turn on railB
                        railB_en.write(true);
                    }

                    if (((m_regs[0x2F] & 0x08) == 0x00) && !railC_ramp) {
                        // turn off railC
                        railC_en.write(false);
                    }
                    else if (((m_regs[0x2F] & 0x08) == 0x08) && railC_ramp) {
                        // turn on railC
                        railC_en.write(true);
                    }
                }
    
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
                else {
                    if (m_bulk_ovr) {
                        m_state = pmic_state_t::P2_A2;
                    }
                }

                break;
            }
            case pmic_state_t::P2_A2: {
                // if we have lost power, go OFFLINE; otherwise go to CONFIG
                if (m_bulk_uvr) {
                    ldo_ramp_en.write(false);
                    m_state = pmic_state_t::P0;
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
                    if (m_vren && secured) {
                        r32_locked = true;
                    }
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
