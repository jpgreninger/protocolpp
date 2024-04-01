#include "tb.h"

void tb::run() {

    uint32_t bulk_volt = 0;
    uint8_t data_reg = 0;

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    // read R32 for read-update-write
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();
    data_reg |= 0x80;

    wait(1, SC_NS);

    // write VR_EN
    wrb_out.write(true);
    wait(1, SC_NS);
    std::cout << "Write VR_EN=1" << std::endl;
    addr_out.write(jpmic::pmicreg_t::R32);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);

    wait(15, SC_MS);
    std::cout << "RailA enabled to 1100mV, at: " << (int)railA_in.read() << std::endl;
    std::cout << "RailB enabled to 1100mV, at: " << (int)railB_in.read() << std::endl;
    std::cout << "RailC enabled to 1800mV, at: " << (int)railC_in.read() << std::endl;
    std::cout << "VDI 1.8v enabled to 1800mV, at: " << (int)v1p8_in.read() << std::endl;
    std::cout << "VDI 1.0v enabled to 1000mV, at: " << (int)v1p0_in.read() << std::endl;
    std::cout << "PWRGD floats, at: " << pwrgd_inout.read() << std::endl;

    wait(5, SC_MS);

    // read R32 for read-update-write
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();

    // Disable VR_EN
    wrb_out.write(true);
    wait(1, SC_NS);
    std::cout << std::endl << "Write VR_EN=0" << std::endl;
    addr_out.write(jpmic::pmicreg_t::R32);
    data_out.write(0x7F & data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);

    wait(5, SC_MS);

    std::cout << "RailA enabled to 1100mV, at: " << (int)railA_in.read() << std::endl;
    std::cout << "RailB enabled to 1100mV, at: " << (int)railB_in.read() << std::endl;
    std::cout << "RailC enabled to 1800mV, at: " << (int)railC_in.read() << std::endl;
    std::cout << "VDI 1.8v enabled to 1800mV, at: " << (int)v1p8_in.read() << std::endl;
    std::cout << "VDI 1.0v enabled to 1000mV, at: " << (int)v1p0_in.read() << std::endl;
    std::cout << "PWRGD asserted, at: " << pwrgd_inout.read() << std::endl;

    wait(5, SC_MS);

    // read R32 for read-update-write
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();
    data_reg |= 0x80;

    wait(1, SC_NS);

    // write VR_EN
    vren_out.write(true);
    std::cout << std::endl << "Assert VR_EN pin=1" << std::endl;

    wait(10, SC_MS);

    std::cout << "RailA enabled to 1100mV, at: " << (int)railA_in.read() << std::endl;
    std::cout << "RailB enabled to 1100mV, at: " << (int)railB_in.read() << std::endl;
    std::cout << "RailC enabled to 1800mV, at: " << (int)railC_in.read() << std::endl;
    std::cout << "VDI 1.8v enabled to 1800mV, at: " << (int)v1p8_in.read() << std::endl;
    std::cout << "VDI 1.0v enabled to 1000mV, at: " << (int)v1p0_in.read() << std::endl;
    std::cout << "PWRGD floats, at: " << pwrgd_inout.read() << std::endl;

    wait(1, SC_MS);

    sc_stop();
}
