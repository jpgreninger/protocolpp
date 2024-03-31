#ifndef JRAIL_H_
#define JRAIL_H_

#include <systemc.h>

class jrail : sc_module {

public:

    sc_in<bool> clk_in;
    sc_in<bool> enable_in;
    sc_in<uint32_t> volt_in;
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
                                    volt_in("volt_in"),
                                    rail_out("rail_out"),
                                    pwrgd_out("pwrgd_out"),
                                    zero_out("zero_out"),
                                    m_rail(rail),
                                    m_volt(0),
                                    m_update(false),
                                    m_enable(false),
                                    m_nvolt(0)

    {
        SC_CTHREAD(enable, clk_in.pos());
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
    bool m_update;
    bool m_enable;
    uint32_t m_nvolt;
};

#endif // JRAIL_H_
