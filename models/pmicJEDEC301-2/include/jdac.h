#ifndef JDAC_H_
#define JDAC_H_

///
///\class jdac JDAC "include/jdac.h"
///
///\section JDAC Analog-to-Digital (ADC) model
///
/// ADC model for use in PMICs
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
        TEMP    = 0x07,
        ENABLE  = 0x08,
        DISABLE = 0x09
    };

    ////////////////////////////////////////////////////
    /// SystemC input ports
    ////////////////////////////////////////////////////
    sc_in<bool> clk_in;
    sc_in<bool> pwrsum_in;
    sc_in<uint8_t> cmd_in;
    sc_in<uint8_t> temp_in;

    ////////////////////////////////////////////////////
    /// SystemC output ports
    ////////////////////////////////////////////////////
    sc_out<uint8_t> data_out;

    ////////////////////////////////////////////////////
    /// Constructor
    /// @param samples - Number of sample in average calculation
    /// @param sample_time - Sample time in nanoseconds
    /// @param rails - Structure with rail configuration
    ////////////////////////////////////////////////////
    SC_CTOR(jdac,
            uint32_t samples,
            uint64_t sample_time,
            std::shared_ptr<std::vector<jrail*>>& rails) : clk_in("clk_in"),
                                                           pwrsum_in("pwrsum_en"),
                                                           cmd_in("cmd_in"),
                                                           temp_in("temp_in"),
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
    /// ---------------------------------
    /// | 4-bit channel | 4-bit command |
    /// ---------------------------------
    ///
    /// Example command for rail 9 voltage average is
    /// 
    /// 0x92
    ///
    /// <table>
    /// <caption id="DAC Commands">DAC Commands</caption>
    /// <tr><th>command<th>value
    /// <tr><td>voltage<td>0x01
    /// <tr><td>voltage avg avg<td>0x02
    /// <tr><td>current<td>0x03
    /// <tr><td>current avg<td>0x04
    /// <tr><td>power<td>0x05
    /// <tr><td>power avg<td>0x06
    /// <tr><td>temp<td>0x07
    /// <tr><td>enable<td>0x08
    /// <tr><td>disable<td>0x09
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
