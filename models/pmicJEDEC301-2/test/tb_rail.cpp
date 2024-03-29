#include "tb_rail.h"

void tb_rail::run_rail() {
    enable_out.write(true);

    wait(2000, SC_MS);

    std::cout << "Rail enabled to 1100mV, at: " << rail_in.read() << std::endl;

    wait(200, SC_MS);

    enable_out.write(false);

    wait(2000, SC_MS);

    std::cout << "Rail disabled, at: " << rail_in.read() << std::endl;

    volt_out.write(1500);
    enable_out.write(true);

    wait(2000, SC_MS);

    std::cout << "Rail enabled to 1100mV, at: " << rail_in.read() << std::endl;

    wait(200, SC_MS);
}
