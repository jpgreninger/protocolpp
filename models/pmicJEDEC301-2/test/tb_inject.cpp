#include "tb.h"

void tb::run() {

    std::cout << sc_time_stamp().to_string() << " PMIC test ERROR INJECTION..." << std::endl;

    uint32_t bulk_volt = 0;
    uint8_t data_reg = 0;
    int errcnt = 0;
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
    std::cout << sc_time_stamp().to_string() << " Test error injection in configuration mode..." << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x90;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWA OVR = 0x90" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0A);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x80) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWA OVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWA OVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xB0;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWB OVR = 0xB0" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0A);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x20) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWB OVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWB OVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xC0;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWC OVR = 0xC0" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0A);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x10) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWC OVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWC OVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xD0;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, BULK OVR = 0xD0" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R08);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if ((data_reg & 0x01) == 0x01) {
        std::cout << sc_time_stamp().to_string() << " PASS: BULK OVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: BULK OVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x98;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWA UVR = 0x98" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0B);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x08) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWA UVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWA UVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xB8;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWB UVR = 0xB8" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0B);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x02) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWB UVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWB UVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xC8;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWC UVR = 0xC8" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0B);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x01) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWC UVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWC UVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xD8;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, BULK UVR = 0xD8" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 0mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 0mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

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
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x82;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, TEMP SHUTDN = 0x82" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R08);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if ((data_reg & 0x40) == 0x40) {
        std::cout << sc_time_stamp().to_string() << " PASS: CRIT TEMP Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: CRIT TEMP Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl << std::endl;

    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x83;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, HIGH TEMP WARN = 0x83" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R09 for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R09);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x80) {
        std::cout << sc_time_stamp().to_string() << " PASS: HIGH TEMP Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: HIGH TEMP Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl << std::endl;

    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x84;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, LDO 1.8v PG = 0x84" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R09 for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R09);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x20) {
        std::cout << sc_time_stamp().to_string() << " PASS: LDO 1.8v PG Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: LDO 1.8v PG Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl << std::endl;

    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x85;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, HIGH CURR Consumption WARN = 0x85" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R09 for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R09);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x0B) {
        std::cout << sc_time_stamp().to_string() << " PASS: HIGH CURR Consumption Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: HIGH CURR Consumption Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl << std::endl;


    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x87;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, CURR Limiter WARN = 0x87" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R09 for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0B);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0xB0) {
        std::cout << sc_time_stamp().to_string() << " PASS: CURR Limiter WARN Status set at: " << std::to_string(data_reg) << std::endl << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: CURR Limiter WARN Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

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
    // Rerun all error injections after rails have ramped in programmable mode
    //////////////////////////////////////////////////////////////////////////////////
    std::cout << sc_time_stamp().to_string() << " ------------------------------------------------- " << std::endl;
    std::cout << sc_time_stamp().to_string() << " * Rerun in programmable mode with rails enabled * " << std::endl;
    std::cout << sc_time_stamp().to_string() << " ------------------------------------------------- " << std::endl << std::endl;

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xB0;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWB OVR = 0xB0" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0A);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x20) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWB OVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWB OVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xC0;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWC OVR = 0xC0" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0A);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x10) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWC OVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWC OVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xD0;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, BULK OVR = 0xD0" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R08);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if ((data_reg & 0x01) == 0x01) {
        std::cout << sc_time_stamp().to_string() << " PASS: BULK OVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: BULK OVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x98;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWA UVR = 0x98" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0B);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x08) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWA UVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWA UVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xB8;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWB UVR = 0xB8" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0B);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x02) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWB UVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWB UVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xC8;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, SWC UVR = 0xC8" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0B);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x01) {
        std::cout << sc_time_stamp().to_string() << " PASS: SWC UVR Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: SWC UVR Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0xD8;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, BULK UVR = 0xD8" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 0mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 0mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x82;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, TEMP SHUTDN = 0x82" << std::endl;
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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 0mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 0) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 0mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R0A for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R08);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if ((data_reg & 0x40) == 0x40) {
        std::cout << sc_time_stamp().to_string() << " PASS: CRIT TEMP Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: CRIT TEMP Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl << std::endl;

    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x83;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, HIGH TEMP WARN = 0x83" << std::endl;
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
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R09 for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R09);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x80) {
        std::cout << sc_time_stamp().to_string() << " PASS: HIGH TEMP Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: HIGH TEMP Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl << std::endl;

    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x84;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, LDO 1.8v PG = 0x84" << std::endl;
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
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R09 for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R09);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x20) {
        std::cout << sc_time_stamp().to_string() << " PASS: LDO 1.8v PG Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: LDO 1.8v PG Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl << std::endl;

    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x85;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, HIGH CURR Consumption WARN = 0x85" << std::endl;
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
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R09 for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R09);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0x0B) {
        std::cout << sc_time_stamp().to_string() << " PASS: HIGH CURR Consumption Status set at: " << std::to_string(data_reg) << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: HIGH CURR Consumption Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl << std::endl;


    wait(10, SC_MS);
    vren_out.write(false);

    while(bulk_volt < 5000) {
        bulk_volt += 50;
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED up: " << (int)bulk_volt << std::endl << std::endl;

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
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB enabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC enabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R35 for read-update-write
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_PS);
    data_reg = data_in.read();
    data_reg |= 0x87;

    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // write VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R35);
    wait(1, SC_NS);
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Write ERR_EN=1, CURR Limiter WARN = 0x87" << std::endl;
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
        std::cout << sc_time_stamp().to_string() << " PASS: RailA disabled to 1100mV, at: " << railA << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailA enabled to 1100mV, failed at: " << railA << std::endl;
    }

    if (railB == 1100) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailB disabled to 1100mV, at: " << railB << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailB enabled to 1100mV, failed at: " << railB << std::endl;
    }

    if (railC == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: RailC disabled to 1800mV, at: " << railC << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: RailC enabled to 1800mV, failed at: " << railC << std::endl;
    }

    if (v1p8ldo == 1800) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.8v enabled to 1800mV, at: " << v1p8ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.8v enabled to 1800mV, failed at: " << v1p8ldo << std::endl;
    }

    if (v1p0ldo == 1000) {
        std::cout << sc_time_stamp().to_string() << " PASS: VDI 1.0v enabled to 1000mV, at: " << v1p0ldo << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: VDI 1.0v enabled to 1000mV, failed at: " << v1p0ldo << std::endl;
    }

    std::cout << sc_time_stamp().to_string() << " PWRGD floats, at: " << pwrgd_inout.read() << std::endl << std::endl;

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // read R09 for status
    //////////////////////////////////////////////////////////////////////////////////
    addr_out.write(jpmic::pmicreg_t::R0B);
    wait(1, SC_PS);
    data_reg = (int)data_in.read();

    if (data_reg == 0xB0) {
        std::cout << sc_time_stamp().to_string() << " PASS: CURR Limiter WARN Status set at: " << std::to_string(data_reg) << std::endl << std::endl;
    }
    else {
        errcnt++;
        std::cerr << sc_time_stamp().to_string() << " FAIL: CURR Limiter WARN Status failed at: " << std::to_string(data_reg) << std::endl << std::endl;
    }

    wait(5, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    wait(1, SC_MS);

    if (errcnt != 0) {
        std::cerr << sc_time_stamp().to_string() << " ***** Simulation FAILED, errors: " << errcnt << " *****" << std::endl;
    }
    else {
        std::cout << sc_time_stamp().to_string() << " ***** Simulation PASSED *****" << std::endl;
    }

    sc_stop();
}
