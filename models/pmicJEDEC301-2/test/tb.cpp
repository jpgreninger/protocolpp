#include "tb.h"

void tb::run() {

    std::cout << sc_time_stamp().to_string() << " PMIC test in SECURE_MODE..." << std::endl;

    uint32_t bulk_volt = 0;
    uint8_t data_reg = 0;
    int railA = 0;
    int railB = 0;
    int railC = 0;
    int v1p8ldo = 0;
    int v1p0ldo = 0;

    //////////////////////////////////////////////////////////////////////////////////
    // drive the bulk input
    //////////////////////////////////////////////////////////////////////////////////
    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Test secure mode with PWRGD set to output only, R32 locked
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Test secure mode with PWRGD set to output only, R32 locked" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x80;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should enable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=0, has no effect" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(0x7F & data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(5, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    vren_out.write(true);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=1, has no effect" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(1, SC_MS);

    pwrgd_inout.write(sc_dt::SC_LOGIC_0);
    wait(10, SC_MS);
    std::cout << sc_time_stamp().to_string() << " PWRGD deasserted, no effect set to output only: " << pwrgd_inout.read() << std::endl;
    wait(1, SC_MS);
    pwrgd_inout.write(sc_dt::SC_LOGIC_Z);
    wait(1, SC_MS);
    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, no effect set to output only: " << pwrgd_inout.read() << std::endl << std::endl;

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl << std::endl;
    }

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x80;

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 has no effect" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // Detach power
    //////////////////////////////////////////////////////////////////////////////////
    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl;
    wait(10, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // Reattach power
    //////////////////////////////////////////////////////////////////////////////////
    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    /// Test secure mode with PWRGD set to input/output, use external PWRGD to power
    /// down and unlock R32. Write VR_EN=1 to restart
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Test secure mode with PWRGD set to input/output, use external" << std::endl;
    std::cout << sc_time_stamp().to_string() << " PWRGD to power down and unlock R32. Write VR_EN=1 to restart" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xA0;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should enable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=0 should have no effect" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(0x7F & data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(5, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    vren_out.write(true);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=1 should have no effect" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(1, SC_MS);

    pwrgd_inout.write(sc_dt::SC_LOGIC_0);
    wait(10, SC_MS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " PWRGD deasserted, should disable rails: " << pwrgd_inout.read() << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wait(1, SC_MS);
    pwrgd_inout.write(sc_dt::SC_LOGIC_Z);
    wait(1, SC_MS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, should have no effect: " << pwrgd_inout.read() << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl << std::endl;
    }

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x80;

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should reenable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl;
    wait(10, SC_MS);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    /// Test secure mode with QUIESCENT mode disabled, use VR_EN to enable/reenable rails
    //////////////////////////////////////////////////////////////////////////////////
   
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Test secure mode with QUIESCENT mode disabled, use VR_EN to enable/reenable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x80;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should enable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    vren_out.write(true);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=1, should have no effect" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(5, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl << std::endl;
    }

    wait(6, SC_MS);

    vren_out.write(false);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=0, should disable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl << std::endl;
    }

    wait(6, SC_MS);

    vren_out.write(true);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=1, should re-enable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    wait(6, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl;
    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    /// Test secure mode with QUIESCENT mode enabled, use VR_EN to enable/reenable rails
    //////////////////////////////////////////////////////////////////////////////////
   
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Test secure mode with QUIESCENT mode enabled, use VR_EN to enable/reenable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R1A for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R1A);
    data_reg = data_in.read();
    data_reg |= 0x10;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write programmable mode
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R1A);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R1A[4]=1, enable Quiescent mode..." << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x80;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should enable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    vren_out.write(true);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=1, should have no effect" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(1, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl << std::endl;
    }

    wait(6, SC_MS);

    vren_out.write(false);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=0, should disable rails and LD0" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v disabled to 0mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v disabled to 0mV, at: " << v1p0ldo << std::endl << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl << std::endl;
    }

    wait(6, SC_MS);

    vren_out.write(true);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=1, should re-enable rails and LD0" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    wait(6, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl;
    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    /// Test programmable mode with QUIESCENT mode
    //////////////////////////////////////////////////////////////////////////////////
   
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Test programmable mode with QUIESCENT mode" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R1A for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R1A);
    data_reg = data_in.read();
    data_reg |= 0x10;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write quiescent mode
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R1A);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " Write R1A[4]=1, enable Quiescent mode..." << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R2F for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    data_reg = data_in.read();
    data_reg |= 0x04;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write programmable mode
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " Write R2F[2]=1, enable Programmable Mode..." << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();
    wait(1, SC_NS);
    data_reg |= 0x80;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should enable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=0, should disable rails and LDOs" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(0x7F & data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(5, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v disabled to 0mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v disabled to 0mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();
    wait(1, SC_NS);
    data_reg |= 0x80;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1, should have no effect" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v disabled to 0mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v disabled to 0mV, at: " << v1p0ldo << std::endl << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl << std::endl;
    }

    wait(6, SC_MS);

    vren_out.write(true);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Assert VR_EN pin=1, should re-enable rails and LD0" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(10, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    wait(6, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl;
    wait(10, SC_MS);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    /// Test programmable mode. Use VREN=0 to disable, VREN=1 to reenable
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Test programmable mode. Use VREN=0 to disable, VREN=1 to reenable" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R2F for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    data_reg = data_in.read();
    data_reg |= 0x04;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write programmable mode
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R2F[2]=1, enable Programmable Mode..." << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();
    wait(1, SC_NS);
    data_reg |= 0x80;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should enable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=0 should disable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(0x7F & data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(5, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    data_reg = data_in.read();
    wait(1, SC_NS);
    data_reg |= 0x80;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should reenable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    wait(6, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl;
    wait(10, SC_MS);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    /// Test programmable mode. Use R2F to turn on/off individual rails
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Test programmable mode. Use R2F to turn on/off individual rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R2F for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    data_reg = data_in.read();
    data_reg |= 0x04;

    //////////////////////////////////////////////////////////////////////////////////
    // write programmable mode
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R2F[2]=1, enable Programmable Mode..." << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    data_reg = data_in.read();
    data_reg |= 0x80;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R32);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write VR_EN=1 should enable rails" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    data_reg = data_in.read();
    data_reg &= 0xBF;

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R2F=0x18 should disable railA" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(5, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    data_reg = data_in.read();
    data_reg &= 0xAF;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R2F=0x08 should disable railB" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    data_reg = data_in.read();
    data_reg &= 0xA7;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R2F=0x00 should disable railC" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    data_reg = data_in.read();
    data_reg |= 0x08;

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R2F=0x08 should enable railC" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(5, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 0mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD asserted, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    data_reg = data_in.read();
    data_reg |= 0x10;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R2F=0x10 should enable railB" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 0mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(6, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R32 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    data_reg = data_in.read();
    data_reg |= 0x40;

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R2F);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write R2F=0x40 should enable railA" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;
    wrb_out.write(true);
    data_out.write(data_reg);
    wait(1, SC_NS);
    wrb_out.write(false);
    addr_out.write(0);

    wait(15, SC_MS);

    railA = (int)railA_in.read();
    railB = (int)railB_in.read();
    railC = (int)railC_in.read();
    v1p8ldo = (int)v1p8_in.read();
    v1p0ldo = (int)v1p0_in.read();

    if (railA == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailA enabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl;

    wait(1, SC_MS);

    sc_stop();
}
