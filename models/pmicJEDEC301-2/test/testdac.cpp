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
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include "top_dac.h"
#include "jdac.h"
#include "jrail.h"
#include "optionparser.h"

enum  optionIndex { UNKNOWN, HELP, LOG };

const option::Descriptor usage[] =
{
 {UNKNOWN, 0,"" , ""    ,option::Arg::None, "USAGE: testrail [options]\n\n"
                                            "Options:" },
 {HELP,   0,"h", "help",option::Arg::None, "  --help, -h \tPrint usage and exit" },
 {LOG,    0,"l", "log",option::Arg::Required, "  --log, -l \tPath to output simulation log" },
 {UNKNOWN, 0,"", ""   ,option::Arg::None, "\nExamples:\n"
                                            "  testrail --log filelog\n" },
 {0,0,nullptr,nullptr}
};

int main(int argc, char* argv[]) {

    // variables
    std::string log("./protocolppDebug.log");

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

    sc_trace_file* file = sc_create_vcd_trace_file("trace_dac"); // open trace file

    TOPDAC top("topdac");
    sc_trace(file, top.clk_in, "clk");
    sc_trace(file, top.railA_en_wire, "railA_en");
    sc_trace(file, top.railB_en_wire, "railB_en");
    sc_trace(file, top.railC_en_wire, "railC_en");
    sc_trace(file, top.railA_out_wire, "railA_voltage");
    sc_trace(file, top.railB_out_wire, "railB_voltage");
    sc_trace(file, top.railC_out_wire, "railC_voltage");
    sc_trace(file, top.cmd_out_wire, "dac_cmds");
    sc_trace(file, top.data_in_wire, "dac_data");
                                  
    sc_start();
    sc_close_vcd_trace_file(file); // close trace file

    return 0;
}

