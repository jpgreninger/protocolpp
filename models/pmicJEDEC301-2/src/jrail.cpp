#include "jrail.h"
#include <cmath>

// enable the rail
void jrail::enable() {
    while(true) {
        wait();

        // we can't just define this to be sensitive to enable.posedge() and enable.negedge()
        // in programmable mode it's possible to adjust the voltage by writing to the register
        if (enable_in.posedge()) {
            // wait for idle time
            wait(m_rail.slewupdly, SC_US);
            zero_out.write(true);
    
            // ramp the rail
            while(abs(m_volt) < abs(m_rail.voltage)) {
                if (m_rail.voltage > 0) {
                    m_volt = (((m_volt+m_rail.slewup) < m_rail.voltage) ? (m_volt+m_rail.slewup) : m_rail.voltage);
                }
                else {
                    m_volt = (((m_volt-m_rail.slewup) > m_rail.voltage) ? (m_volt-m_rail.slewup) : m_rail.voltage);
                }
    
                rail_out.write(m_volt);

                if(abs(m_volt) == abs(m_rail.voltage)) {
                    // assert rail pwrgd
                    pwrgd_out.write(true);
                }
                else {
                    // skew is defined as mV/mS
                    wait(1, SC_MS);
                }
            }
        }
        else if (update_in.posedge() && enable_in.read()) {
            int nvolt  = (int)volt_in.read();

            while(abs(m_volt) != abs(nvolt)) {
                if (nvolt > m_volt) {
                    m_volt = (((m_volt+m_rail.slewup) < nvolt) ? (m_volt+m_rail.slewup) : nvolt);
                }
                else {
                    m_volt = (((m_volt-m_rail.slewdn) > nvolt) ? (m_volt-m_rail.slewdn) : nvolt);
                }
        
                // rail can only change at 1mV/mS
                rail_out.write(m_volt);
                wait(1, SC_MS);
            }
        }
        else if (enable_in.negedge()) {
            // wait for STOP idle time, deassert pwrgd
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
                    // assert zero reached
                    zero_out.write(false);
                }
                else {
                    // skew is defined as mV/mS
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
