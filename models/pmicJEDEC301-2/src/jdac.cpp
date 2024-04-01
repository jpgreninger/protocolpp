#include "jdac.h"

// sample the rails
void jdac::sample() {
    while(true) {
        wait();

        if(m_enable) {
            wait(m_stime/1000000, SC_MS);
            for(size_t i=0; i<m_rails->size(); i++) {
                m_voltavg[i].emplace_back((uint64_t)m_rails->at(i)->voltage());
                m_curravg[i].emplace_back((uint64_t)m_rails->at(i)->current());
                m_powravg[i].emplace_back(m_rails->at(i)->power());
        
                if (m_voltavg[i].size() > m_samples) {
                    m_voltavg[i].pop_front();
                    m_curravg[i].pop_front();
                    m_powravg[i].pop_front();
                }
            }
        }
    }
}

// process commands
void jdac::cmd() {
    while(true) {
        wait();

        // read ports
        uint32_t avg=0;
        uint8_t result=0;
        uint8_t cmds = cmd_in.read();
        uint32_t command=(cmds & 0x0F);
        bool pwrsum = pwrsum_in.read();
        uint8_t currtemp = temp_in.read();
        uint32_t channel=((cmds >> 4) & 0x0F);

        switch(command) {
            case dac_t::VOLTAGE:
                avg = m_voltavg[channel][m_samples-1]/15;
                result = ((avg > 255) ? 255 : avg);
                break;
            case dac_t::VOLTAVG:
                for(size_t i=0; i<m_samples; i++) {
                    avg += m_voltavg[channel][i];
                }
                avg = (avg/m_samples)/15;
                result = ((avg > 255) ? 255 : avg);
                break;
            case dac_t::CURRENT:
                avg = m_curravg[channel][m_samples-1]/125;
                result = ((avg > 63) ? 63 : avg);
                break;
            case dac_t::CURRAVG:
                for(size_t i=0; i<m_samples; i++) {
                    avg += m_curravg[channel][i];
                }
                avg = (avg/m_samples)/125;
                result = ((avg > 63) ? 63 : avg);
                break;
            case dac_t::POWER:
                if (pwrsum) {
                    avg = m_powravg[0][m_samples-1]/125;
                    avg += m_powravg[1][m_samples-1]/125;
                    avg += m_powravg[2][m_samples-1]/125;
                    result = ((avg > 255) ? 255 : avg);
                }
                else {
                    avg = m_powravg[channel][m_samples-1]/125;
                    result = ((avg > 63) ? 63 : avg);
                }
                break;
            case dac_t::POWRAVG:
                if (pwrsum) {
                    for(size_t j=0; j<3; j++) {
                        for(size_t i=0; i<m_samples; i++) {
                            avg += m_powravg[j][i];
                        }
                    }
                    avg = (avg/m_samples)/125;
                    result = ((avg > 255) ? 255 : avg);
                }
                else {
                    for(size_t i=0; i<m_samples; i++) {
                        avg += m_powravg[channel][i];
                    }
                    avg = (avg/m_samples)/125;
                    result = ((avg > 63) ? 63 : avg);
                }
                break;
            case dac_t::TEMP:
                switch (currtemp) {
                    case 85:
                    case 86:
                    case 87:
                    case 88:
                    case 89:
                        result = 0x01;
                        break;
                    case 90:
                    case 91:
                    case 92:
                    case 93:
                    case 94:
                    case 95:
                    case 96:
                    case 97:
                    case 98:
                    case 99:
                        result = 0x02;
                        break;
                    case 100:
                    case 101:
                    case 102:
                    case 103:
                    case 104:
                    case 105:
                    case 106:
                    case 107:
                    case 108:
                    case 109:
                        result = 0x03;
                        break;
                    case 110:
                    case 111:
                    case 112:
                    case 113:
                    case 114:
                    case 115:
                    case 116:
                    case 117:
                    case 118:
                    case 119:
                        result = 0x04;
                        break;
                    case 120:
                    case 121:
                    case 122:
                    case 123:
                    case 124:
                    case 125:
                    case 126:
                    case 127:
                    case 128:
                    case 129:
                        result = 0x05;
                        break;
                    case 130:
                    case 131:
                    case 132:
                    case 133:
                    case 134:
                    case 135:
                    case 136:
                    case 137:
                    case 138:
                    case 139:
                        result = 0x06;
                        break;
                    default:
                        if (currtemp >= 140) {
                            result = 0x07;
                        }
                        else {
                            result = 0;
                        }
                }

                break;
            case dac_t::ENABLE:
                m_enable = true;
                break;
            case dac_t::DISABLE:
                m_enable = false;
                break;
            default:
                result = 0;
        }
    
        data_out.write(result);
    }
}
