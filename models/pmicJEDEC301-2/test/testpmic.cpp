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
#include <iostream>
#include <unistd.h>
#include "jdac.h"
#include "jrail.h"
#include "jpmic.h"
#include "top.h"
#include "optionparser.h"

enum  optionIndex { UNKNOWN, HELP, LOG };

const option::Descriptor usage[] =
{
 {UNKNOWN, 0,"" , ""    ,option::Arg::None, "USAGE: testpmic [options]\n\n"
                                            "Options:" },
 {HELP,   0,"h", "help",option::Arg::None, "  --help, -h \tPrint usage and exit" },
 {LOG,    0,"l", "log",option::Arg::Required, "  --log, -l \tPath to output simulation log" },
 {UNKNOWN, 0,"", ""   ,option::Arg::None, "\nExamples:\n"
                                            "  testpmic --log filelog\n" },
 {0,0,nullptr,nullptr}
};

int main(int argc, char* argv[]) {

    // variables
    std::string log("./testPmic.log");

    // skip program name argv[0] if present
    argc-=(argc>0); argv+=(argc>0);
    option::Stats  stats(usage, argc, argv);
    option::Option options[4], buffer[2];
    option::Parser parse(usage, argc, argv, options, buffer);

    // parse options
    if (parse.error()) {
        exit(EXIT_FAILURE);
    }

    // print help
    if (options[HELP] || argc == 0) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    // parse options
    for (option::Option* opt = options[LOG]; opt; opt = opt->next())
        log = std::string(opt->arg); 


    sc_trace_file* file = sc_create_vcd_trace_file("trace_pmic"); // open trace file

    TOP top("top");
    sc_trace(file, top.bulk_out, "bulk_voltage");
    sc_trace(file, top.vren_wire, "vren");
    sc_trace(file, top.gsi_n, "gsi_n");
    sc_trace(file, top.pwrgd, "pwrgd");
    sc_trace(file, top.wrb, "wrb");
    sc_trace(file, top.addr_in, "addr_in");
    sc_trace(file, top.data_in, "data_in");
    sc_trace(file, top.railA_out, "railA_out");
    sc_trace(file, top.railB_out, "railB_out");
    sc_trace(file, top.railC_out, "railC_out");
    sc_trace(file, top.v1p8_out, "v1p8_out");
    sc_trace(file, top.v1p0_out, "v1p0_out");

    // wires
    sc_trace(file, top.pmic->m_stateint, "pstate_int");
    sc_trace(file, top.pmic->m_state, "pstate");
    sc_trace(file, top.pmic->cmd_in, "dac_cmd");
    sc_trace(file, top.pmic->temp_in, "temp");
    sc_trace(file, top.reg_data_out, "reg_data_out");
    sc_trace(file, top.pmic->railA_en, "railA_en");
    sc_trace(file, top.pmic->railB_en, "railB_en");
    sc_trace(file, top.pmic->railC_en, "railC_en");
    sc_trace(file, top.pmic->railA_pwrgd, "railA_pwrgd");
    sc_trace(file, top.pmic->railB_pwrgd, "railB_pwrgd");
    sc_trace(file, top.pmic->railC_pwrgd, "railC_pwrgd");
    sc_trace(file, top.pmic->railA_zero, "railA_zero");
    sc_trace(file, top.pmic->railB_zero, "railB_zero");
    sc_trace(file, top.pmic->railC_zero, "railC_zero");

    sc_start();
    sc_close_vcd_trace_file(file); // close trace file

    return 0;
}

