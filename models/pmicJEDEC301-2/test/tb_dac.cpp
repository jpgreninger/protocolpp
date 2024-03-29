#include "tb_dac.h"

void tb_dac::run() {

    railA_volt.write(1100);
    railB_volt.write(1100);
    railC_volt.write(1800);

    railA_en.write(true);
    railB_en.write(true);
    railC_en.write(true);

    wait(5, SC_MS);

    // read RailA values
    cmd_out.write(jdac::dac_t::VOLTAGE);
    wait(1, SC_MS);
    std::cout << "RailA voltage at: " << (int)data_in.read() << " encoded, in mV: " << (((int)data_in.read())*15) << std::endl;

    cmd_out.write(jdac::dac_t::VOLTAVG);
    wait(1, SC_MS);
    std::cout << "RailA voltage avg at: " << (int)data_in.read() << " encoded, in mV: " << (((int)data_in.read())*15) << std::endl;

    cmd_out.write(jdac::dac_t::CURRENT);
    wait(1, SC_MS);
    std::cout << "RailA current at: " << (int)data_in.read() << " encoded, in mA: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::CURRAVG);
    wait(1, SC_MS);
    std::cout << "RailA current avg at: " << (int)data_in.read() << " encoded, in mA: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::POWER);
    wait(1, SC_MS);
    std::cout << "RailA power at: " << (int)data_in.read() << " encoded, in mW: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::POWRAVG | 0x10);
    wait(1, SC_MS);
    std::cout << "RailA power avg at: " << (int)data_in.read() << " encoded, in mW: " << (((int)data_in.read())*125) << std::endl << std::endl;

    // read RailB values
    cmd_out.write(jdac::dac_t::VOLTAGE | 0x10);
    wait(1, SC_MS);
    std::cout << "RailB voltage at: " << (int)data_in.read() << " encoded, in mV: " << (((int)data_in.read())*15) << std::endl;

    cmd_out.write(jdac::dac_t::VOLTAVG | 0x10);
    wait(1, SC_MS);
    std::cout << "RailB voltage avg at: " << (int)data_in.read() << " encoded, in mV: " << (((int)data_in.read())*15) << std::endl;

    cmd_out.write(jdac::dac_t::CURRENT | 0x10);
    wait(1, SC_MS);
    std::cout << "RailB current at: " << (int)data_in.read() << " encoded, in mA: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::CURRAVG | 0x10);
    wait(1, SC_MS);
    std::cout << "RailB current avg at: " << (int)data_in.read() << " encoded, in mA: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::POWER | 0x10);
    wait(1, SC_MS);
    std::cout << "RailB power at: " << (int)data_in.read() << " encoded, in mW: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::POWRAVG | 0x10);
    wait(1, SC_MS);
    std::cout << "RailB power avg at: " << (int)data_in.read() << " encoded, in mW: " << (((int)data_in.read())*125) << std::endl << std::endl;

    // read RailC values
    cmd_out.write(jdac::dac_t::VOLTAGE | 0x20);
    wait(1, SC_MS);
    std::cout << "RailC voltage at: " << (int)data_in.read() << " encoded, in mV: " << (((int)data_in.read())*15) << std::endl;

    cmd_out.write(jdac::dac_t::VOLTAVG | 0x20);
    wait(1, SC_MS);
    std::cout << "RailC voltage avg at: " << (int)data_in.read() << " encoded, in mV: " << (((int)data_in.read())*15) << std::endl;

    cmd_out.write(jdac::dac_t::CURRENT | 0x20);
    wait(1, SC_MS);
    std::cout << "RailC current at: " << (int)data_in.read() << " encoded, in mA: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::CURRAVG | 0x20);
    wait(1, SC_MS);
    std::cout << "RailC current avg at: " << (int)data_in.read() << " encoded, in mA: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::POWER | 0x20);
    wait(1, SC_MS);
    std::cout << "RailC power at: " << (int)data_in.read() << " encoded, in mW: " << (((int)data_in.read())*125) << std::endl;

    cmd_out.write(jdac::dac_t::POWRAVG | 0x20);
    wait(1, SC_MS);
    std::cout << "RailC power avg at: " << (int)data_in.read() << " encoded, in mW: " << (((int)data_in.read())*125) << std::endl;

    railA_en.write(false);
    railB_en.write(false);
    railC_en.write(false);

    wait(1, SC_MS);

    sc_stop();
}
