#ifndef JRAIL_H_
#define JRAIL_H_

///
///\class jrail jrail "include/jrail.h"
///
///\section JRAIL Analog rail model
///
/// Model for analog rails with the following features
/// 
/// * Positive or negative voltage
/// * Voltage setting (operating voltage)
/// * Maximum voltage, current, and power
/// * Separate up and down voltage slew rates (mV/mS)
/// * Separate ramp up/down idle times to stagger rail ramps
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

#include <systemc.h>

class jrail : sc_module {

public:

    ////////////////////////////////////////////////////
    /// SystemC input ports
    /// enable_in - Edge-triggered enable for ramping rails
    /// update_in - Posedge triggered enable for updating rail voltage
    /// volt_in - New input voltage to move rail to
    ////////////////////////////////////////////////////
    sc_in<bool> enable_in;
    sc_in<bool> update_in;
    sc_in<uint32_t> volt_in;

    ////////////////////////////////////////////////////
    /// SystemC output ports
    ////////////////////////////////////////////////////
    sc_out<uint32_t> rail_out;
    sc_out<bool> pwrgd_out;
    sc_out<bool> zero_out;
    
    ////////////////////////////////////////////////////
    /// Configuration for this rail
    /// @param voltage - operating voltage
    /// @param resistance - resistance of the rail for current and power calculations
    /// @param max_volt - maximum supported rail voltage
    /// @param max_current - maximum supported rail current
    /// @param max_power - maximum supported rail power
    /// @param slewup - slew rate in mV/ms
    /// @param slewdn - slew rate in mV/ms
    /// @param slewupdly - delay before this rail ramps up (in nanoseconds)
    /// @param slewdndly - delay before this rail ramps down (in nanoseconds)
    ////////////////////////////////////////////////////
    struct railcfg {
        int voltage;
        float resistance;
        int max_volt;
        int max_current;
        int max_power;
        int slewup;
        int slewdn;
        int slewupdly;
        int slewdndly;

        railcfg(int volt,
                float res,
                int maxv,
                int maxc,
                int maxp,
                int sup,
                int sdn,
                int upd,
                int dnd) : voltage(volt),
                           resistance(res),
                           max_volt(maxv),
                           max_current(maxc),
                           max_power(maxp),
                           slewup(sup),
                           slewdn(sdn),
                           slewupdly(upd),
                           slewdndly(dnd) {}
    };

    ////////////////////////////////////////////////////
    /// Constructor
    /// @param rail - Structure with rail configuration
    ////////////////////////////////////////////////////
    SC_CTOR(jrail, railcfg& rail) : enable_in("enable_in"),
                                    update_in("update_in"),
                                    volt_in("volt_in"),
                                    rail_out("rail_out"),
                                    pwrgd_out("pwrgd_out"),
                                    zero_out("zero_out"),
                                    m_rail(rail),
                                    m_volt(0)
    {
        SC_THREAD(enable);
            sensitive << enable_in << update_in;
    }

    ////////////////////////////////////////////////////
    /// Deconstructor
    ////////////////////////////////////////////////////
    ~jrail() = default;

    ////////////////////////////////////////////////////
    /// Enable the rail
    ////////////////////////////////////////////////////
    void enable();

    ////////////////////////////////////////////////////
    /// Return the current voltage
    /// @return Current voltage
    ////////////////////////////////////////////////////
    int voltage();

    ////////////////////////////////////////////////////
    /// Return the immediate current
    /// @return Immediate current
    ////////////////////////////////////////////////////
    int current();

    ////////////////////////////////////////////////////
    /// Return the current power
    /// @return Current power
    ////////////////////////////////////////////////////
    uint64_t power();

private:

    railcfg m_rail;
    int m_volt;
};

#endif // JRAIL_H_
