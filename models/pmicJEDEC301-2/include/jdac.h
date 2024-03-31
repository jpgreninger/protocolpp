#ifndef JDAC_H_
#define JDAC_H_

#include <deque>
#include <memory>
#include <systemc.h>
#include <vector>

#include "jrail.h"

class jdac : public sc_module {

public:

    enum dac_t {
        VOLTAGE = 0x01,
        VOLTAVG = 0x02,
        CURRENT = 0x03,
        CURRAVG = 0x04,
        POWER   = 0x05,
        POWRAVG = 0x06,
        ENABLE  = 0x07,
        DISABLE = 0x08
    };

    sc_in<bool> clk_in;
    sc_in<bool> pwrsum_in;
    sc_in<uint8_t> cmd_in;
    sc_out<uint8_t> data_out;

    ////////////////////////////////////////////////////
    /// Constructor
    /// @param samples - Number of sample in average calculation
    /// @param sample_time - Sample time in nanoseconds
    /// @param rail - Structure with rail configuration
    ////////////////////////////////////////////////////
    SC_CTOR(jdac,
            uint32_t samples,
            uint64_t sample_time,
            std::shared_ptr<std::vector<jrail*>>& rails) : clk_in("clk_in"),
                                                           pwrsum_in("pwrsum_en"),
                                                           cmd_in("cmd_in"),
                                                           data_out("data_out"),
                                                           m_enable(true),
                                                           m_samples(samples),
                                                           m_stime(sample_time),
                                                           m_rails(rails),
                                                           m_voltavg(),
                                                           m_curravg(),
                                                           m_powravg()
    {
        for(size_t i=0; i<rails->size(); i++) {
            m_voltavg.emplace_back(std::deque<uint64_t>(samples,0));
            m_curravg.emplace_back(std::deque<uint64_t>(samples,0));
            m_powravg.emplace_back(std::deque<uint64_t>(samples,0));
        }

        SC_CTHREAD(sample, clk_in.pos());
        SC_CTHREAD(cmd, clk_in.pos());
    }


    ////////////////////////////////////////////////////
    /// Deconstructor
    ////////////////////////////////////////////////////
    ~jdac() = default;

    ////////////////////////////////////////////////////
    /// Samples all voltage, current, and power every
    /// sample_time nanoseconds
    ////////////////////////////////////////////////////
    void sample();

    ////////////////////////////////////////////////////
    /// Command queue for the DAC
    ///
    /// ----------------------------------
    /// | 8-bit channel | 24-bit command |
    /// ----------------------------------
    ///
    /// Example command for rail 9 voltage average is
    /// 
    /// 0x0900002
    ///
    /// <table>
    /// <caption id="DAC Commands">DAC Commands</caption>
    /// <tr><th>command<th>value
    /// <tr><td>voltage<td>0x000001
    /// <tr><td>voltage avg avg<td>0x000002
    /// <tr><td>current<td>0x000003
    /// <tr><td>current avg<td>0x000004
    /// <tr><td>power<td>0x000005
    /// <tr><td>power avg<td>0x000006
    /// <tr><td>enable<td>0x000010
    /// <tr><td>disable<td>0x000020
    /// </table>
    ////////////////////////////////////////////////////
    void cmd();

private:

    bool m_enable;
    uint32_t m_samples;
    uint64_t m_stime;
    std::shared_ptr<std::vector<jrail*>> m_rails;
    std::vector<std::deque<uint64_t>> m_voltavg;
    std::vector<std::deque<uint64_t>> m_curravg;
    std::vector<std::deque<uint64_t>> m_powravg;
};

#endif // JDAC_H_
