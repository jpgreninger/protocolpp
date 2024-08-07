#include "jpmic.h"

// Reset the device (cold, hard, soft)
void jpmic::regs() {

    while(true) {
        wait();

        bool wrb = wrb_in.read();
        uint8_t addr = addr_in.read();
        uint8_t data = data_in.read();
        uint32_t railVolt = 0;

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
                    m_regs[0x08] ^= data;
                    break;
                case 0x11:
                    m_regs[0x09] ^= data;
                    break;
                case 0x12:
                    m_regs[0x0A] ^= data;
                    break;
                case 0x13:
                    m_regs[0x0B] ^= data;
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
                        m_regs[0x0C] ^= (data & 0x04);
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
                                // ADC select for SWA voltage
                                cmd_in.write(0x01);
                                break;
                            case 2:
                                // ADC select for SWB voltage
                                cmd_in.write(0x11);
                                break;
                            case 3:
                                // ADC select for SWC voltage
                                cmd_in.write(0x21);
                                break;
                            default:
                                m_regs[0x31] = m_regs[0x31];
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
                    break;
                case 0x31:
                    if (m_regs[0x30] & 0x80) {
                        switch(m_regs[0x30] & 0x78) {
                            case 0:
                            case 2:
                            case 3:
                                m_regs[0x31] = dac_data_out.read(); 
                                break;
                            case 5: {
                                railVolt = bulk_in->read();
                                m_regs[0x31] = ((railVolt >= 17850) ? 0xFF : railVolt/70);
                                break;
                            }
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
                    else {
                        m_regs[0x31] = 0;
                    }
                    break;
                case 0x33:
                    // sample the temperature
                    cmd_in.write(0x07);
                    m_regs[addr] = (dac_data_out.read() << 5);
                    break;
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

        // bulk input UVR
        m_buvr = (bulk_in_read < m_cfg.bulk_min_volt);

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

        // set SWA, SWB, SWC rails OVR, UVR status bits
        m_regs[0x04] = ((m_errcnt << 7) | ((m_ovr | m_uvr) << 6) | (m_bulk_ovr << 5) | (m_shutdown << 4));
        m_regs[0x05] = ((swa_pg << 6) | (swb_pg << 4) | (swc_pg << 3) | m_errlog);
        m_regs[0x06] = ((m_uvrA << 7) | (m_uvrB << 5) | (m_uvrC << 4) | (m_ovrA << 3) | (m_ovrB << 1) | m_ovrC);
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

        // rail current limit overage
        m_limit = ((m_limitA && ((m_regs[0x18] & 0x80) == 0) && tOutput_Current_Limiter_A_trigger) ||
                   (m_limitB && ((m_regs[0x18] & 0x20) == 0) && tOutput_Current_Limiter_B_trigger) ||
                   (m_limitC && ((m_regs[0x18] & 0x10) == 0) && tOutput_Current_Limiter_C_trigger));

        // rail current high consumption
        m_consum = ((m_consumA && ((m_regs[0x16] & 0x08) == 0)) ||
                    (m_consumB && ((m_regs[0x16] & 0x02) == 0)) ||
                    (m_consumC && ((m_regs[0x16] & 0x01) == 0)));

        // 1.8v power good
        m_v18pg = m_v18 >= m_cfg.v18_setting;

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
                    m_regs = {0x00, 0x00, 0x00, 0x00,                         // 0x00-0x03
                              m_regs[0x04], m_regs[0x05], m_regs[0x06], 0x00, // 0x04-0x07
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x08-0x0F
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x20, 0x00, // 0x10-0x17
                              0x00, 0x04, 0x00, 0x05, 0x60, 0x00, 0x60, 0x60, // 0x18-0x1F
                              m_regs[0x50], m_regs[0x45], m_regs[0x46], m_regs[0x47], // 0x20-0x23
                              m_regs[0x48], m_regs[0x49], m_regs[0x4A], m_regs[0x4B], // 0x24-0x27
                              m_regs[0x4C], m_regs[0x4D], m_regs[0x4E], m_regs[0x51], // 0x28-0x2B
                              m_regs[0x5D], m_regs[0x5E], 0x04, 0x02,         // 0x2C-0x2F
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
                if (m_vren || (vren_in.posedge() && !(m_regs[0x32] & 0x20))) {
                    if (!(m_regs[0x2F] & 0x04)) {
                        // PWRGD low can unlock R32
                        secured = true;
                        r32_locked = true;
                    }

                    m_state = pmic_state_t::RAMPUP;
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
