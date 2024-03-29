#include "jrail.h"
#include <cmath>

// enable the rail
void jrail::enable() {
    while(true) {
        wait();

        m_enable = enable_in.read();
        m_nvolt  = volt_in.read();

        if (m_enable) {
            if (!m_update) {
                wait(m_rail.slewupdly, SC_US);
                zero_out.write(true);
        
                while(abs(m_volt) != abs(m_rail.voltage)) {
                    if (m_rail.voltage > 0) {
                        m_volt = (((m_volt+m_rail.slewup) < m_rail.voltage) ? (m_volt+m_rail.slewup) : m_rail.voltage);
                    }
                    else {
                        m_volt = (((m_volt-m_rail.slewup) > m_rail.voltage) ? (m_volt-m_rail.slewup) : m_rail.voltage);
                    }
        
                    rail_out.write(m_volt);

                    if(abs(m_volt) == abs(m_rail.voltage)) {
                        pwrgd_out.write(true);
                        m_update = true;
                    }
                    else {
                        wait(1, SC_MS);
                    }
                }
            }
            else if (m_volt != m_nvolt) {
                // updates allowed
                while(m_volt != m_nvolt) {
                    if (m_nvolt > m_volt) {
                        m_volt = (((m_volt+m_rail.slewup) < m_nvolt) ? (m_volt+m_rail.slewup) : m_nvolt);
                    }
                    else {
                        m_volt = (((m_volt-m_rail.slewdn) > m_nvolt) ? (m_volt-m_rail.slewdn) : m_nvolt);
                    }
            
                    rail_out.write(m_volt);
                    wait(1, SC_MS);
                }
                std::cout << basename() << " Updated voltage reached: " << m_volt << std::endl;
            }
        }
        else {
            wait(m_rail.slewdndly, SC_US);
            pwrgd_out.write(false);
    
            while(m_volt != 0) {
                if (m_rail.voltage > 0) {
                    m_volt = (((m_volt-m_rail.slewdn) > 0) ? (m_volt-m_rail.slewdn) : 0);
                }
                else {
                    m_volt = (((m_volt+m_rail.slewdn) < 0) ? (m_volt+m_rail.slewdn) : 0);
                }
        
                rail_out.write(m_volt);

                if (m_volt == 0) {
                    zero_out.write(false);
                    m_update = false;
                }
                else {
                    wait(1, SC_MS);
                }
            }
        }
    }
}

// get the voltage
int jrail::voltage() {
    return m_volt;
}

// get the current
int jrail::current() {
    return (m_volt/m_rail.resistance);

}

// get the power
uint64_t jrail::power() {
    return ((uint64_t)((m_volt*m_volt)/m_rail.resistance));
}
