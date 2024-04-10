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
#include <string>
#include <iostream>
#include "top_rail.h"
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
 {0,0,nullptr}
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

    sc_trace_file* file = sc_create_vcd_trace_file("trace_rail"); // open trace file

    TOPRAIL top("toprail");
    sc_trace(file, top.enable_wire, "enable");
    sc_trace(file, top.volt_wire, "volt_in");
    sc_trace(file, top.rail_wire, "rail_voltage");
    sc_trace(file, top.rail->update_in, "update");
    sc_trace(file, top.rail->enable_in, "enable");
    sc_trace(file, top.rail->volt_in, "new_volt");
                                  
    sc_start();
    sc_close_vcd_trace_file(file); // close trace file

    return 0;
}

