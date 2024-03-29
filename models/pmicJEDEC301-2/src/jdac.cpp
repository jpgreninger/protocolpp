#include "jdac.h"

// sample the rails
void jdac::sample() {
    while(true) {
        wait();

        if(m_enable) {
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
