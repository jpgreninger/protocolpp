#ifndef TB_H_
#define TB_H_

///
///\class tb tb "include/tb.h"
///
///\section TB Power Management IC testbench module 
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
#include "jpmic.h"

SC_MODULE(tb) {

    /////////////////////////////////////////////////////
    /// SystemC inout ports
    /////////////////////////////////////////////////////
    sc_in<bool> pwrgd_inout;

    /////////////////////////////////////////////////////
    /// SystemC input ports
    /////////////////////////////////////////////////////
    sc_in<bool> clk_in;
    sc_in<bool> gsi_n_in;
    sc_in<uint8_t> data_in;
    sc_in<uint32_t> v1p8_in;
    sc_in<uint32_t> v1p0_in;
    sc_in<uint32_t> railA_in;
    sc_in<uint32_t> railB_in;
    sc_in<uint32_t> railC_in;

    /////////////////////////////////////////////////////
    /// SystemC output ports
    /////////////////////////////////////////////////////
    sc_out<bool> vren_out;
    sc_out<bool> wrb_out;
    sc_out<uint8_t> addr_out;
    sc_out<uint8_t> data_out;
    sc_out<uint32_t> bulk_out;

    void run();

    /////////////////////////////////////////////////////
    /// SystemC constructor
    /////////////////////////////////////////////////////
    SC_CTOR(tb) : pwrgd_inout("pwrgd_inout"),
                  clk_in("clk_in"),
                  gsi_n_in("gsi_n_in"),
                  data_in("data_in"),
                  v1p8_in("v1p8_in"),
                  v1p0_in("v1p0_in"),
                  railA_in("railA_in"),
                  railB_in("railB_in"),
                  railC_in("railC_in"),
                  vren_out("vren_out"),
                  wrb_out("wrb_out"),
                  addr_out("addr_out"),
                  data_out("data_out"),
                  bulk_out("bulk_out")
    {
        SC_CTHREAD(run, clk_in.pos());
    }
};

#endif // TB_H_
