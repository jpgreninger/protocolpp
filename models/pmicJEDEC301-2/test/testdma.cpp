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

#include <iostream>
#include <thread>
#include <tuple>
#include "jdma.h"
#include "optionparser.h"

enum  optionIndex { UNKNOWN, HELP, LOG };

const option::Descriptor usage[] =
{
 {UNKNOWN, 0,"" , ""    ,option::Arg::None, "USAGE: testdma [options]\n\n"
                                            "Options:" },
 {HELP,   0,"h", "help",option::Arg::None, "  --help, -h \tPrint usage and exit" },
 {LOG,    0,"l", "log",option::Arg::Required, "  --log, -l \tPath to output simulation log" },
 {UNKNOWN, 0,"", ""   ,option::Arg::None, "\nExamples:\n"
                                            "  testrail --log filelog\n" },
 {0,0,nullptr,nullptr}
};

int main(int argc, char* argv[]) {

    // variables
    std::string log("./testdma.log");

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

    jdma dma;

    uint8_t* src  = new uint8_t[256];
    uint8_t* dst  = new uint8_t[256];
    uint8_t* dst2 = new uint8_t[256];

    // fill the source array
    for(int i=0; i<256; i++) {
        uint8_t tmp = (uint8_t)(rand()%255);
        src[i] = tmp;
    }

    auto tmp = std::make_tuple<size_t, uintptr_t, uintptr_t>(256, (uintptr_t)src, (uintptr_t)dst2);

    dma.cmd(256, (uintptr_t)src, (uintptr_t)dst);
    dma.cmd(tmp);
    dma.process();
    dma.process();

    for(int i=0; i<256; i++) {
        if (src[i] != dst[i]) {
            std::cout << "Copy to DST1 failed at index: " << i << std::endl;
        }
        if (src[i] != dst2[i]) {
            std::cout << "Copy to DST2 failed at index: " << i << std::endl;
        }
    }

    delete [] src;
    delete [] dst;
    delete [] dst2;

    return 0;
}

