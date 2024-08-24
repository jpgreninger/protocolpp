#include "tb.h"
#include <iomanip>

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
    std::cout << sc_time_stamp().to_string() << " Unlock the registers" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(5, SC_MS);

    data_reg = 0x73;

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R37);
    data_out.write(data_reg);
    wait(1, SC_NS);

    data_reg = 0x94;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R38);
    data_out.write(data_reg);
    wait(1, SC_NS);

    data_reg = 0x40;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R39);
    data_out.write(data_reg);

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // Test secure mode with PWRGD set to output only, R32 locked
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Clear registers 0x04-0x07" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    data_reg = 0x74;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R39);
    data_out.write(data_reg);
    wait(1, SC_NS);

    //////////////////////////////////////////////////////////////////////////////////
    // Disable VR_EN
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Change password" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    data_reg = 0x37;
    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R37);
    data_out.write(data_reg);
    wait(1, SC_NS);

    data_reg = 0x49;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R38);
    data_out.write(data_reg);
    wait(1, SC_NS);

    data_reg = 0x80;

    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Burn new password (takes 200ms)" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R39);
    data_out.write(data_reg);
    wait(200, SC_MS);

    // check for burn completion
    while (data_reg != 0x5A) {
        wrb_out.write(false);
        addr_out.write(jpmic::pmicreg_t::R39);
        wait(1, SC_PS);
        data_reg = data_in.read();
    }

    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Burn Completed" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // Test secure mode with PWRGD set to output only, R32 locked
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Lock registers" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    data_reg = 0x00;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R39);
    data_out.write(data_reg);

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
    // Register unlock
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Unlock the registers with new password" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    wait(5, SC_MS);

    data_reg = 0x37;

    //////////////////////////////////////////////////////////////////////////////////
    // Unlock registers with new password
    //////////////////////////////////////////////////////////////////////////////////
    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R37);
    data_out.write(data_reg);
    wait(1, SC_NS);

    data_reg = 0x49;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R38);
    data_out.write(data_reg);
    wait(1, SC_NS);

    data_reg = 0x40;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R39);
    data_out.write(data_reg);

    wait(5, SC_MS);

    //////////////////////////////////////////////////////////////////////////////////
    // Read out the new password
    //////////////////////////////////////////////////////////////////////////////////
    wrb_out.write(false);
    addr_out.write(jpmic::pmicreg_t::R37);
    wait(1, SC_PS);
    data_reg = data_in.read();

    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Read new password (should read zero)" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " LSB = 0x" << std::hex << (int)data_reg << std::endl;

    wrb_out.write(false);
    addr_out.write(jpmic::pmicreg_t::R38);
    wait(1, SC_PS);
    data_reg = data_in.read();
    std::cout << sc_time_stamp().to_string() << " MSB = 0x" << (int)data_reg << std::dec << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////////////
    // Test secure mode with PWRGD set to output only, R32 locked
    //////////////////////////////////////////////////////////////////////////////////
    
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl;
    std::cout << sc_time_stamp().to_string() << " Lock registers" << std::endl;
    std::cout << sc_time_stamp().to_string() << " --------------------------------------------" << std::endl << std::endl;

    data_reg = 0x00;

    wrb_out.write(true);
    addr_out.write(jpmic::pmicreg_t::R39);
    data_out.write(data_reg);

    wait(6, SC_MS);

    while(bulk_volt != 0) {
        bulk_volt = ((bulk_volt-50 < 0) ? 0 : bulk_volt-50);
        bulk_out.write(bulk_volt);
        wait(1, SC_NS);
    }

    std::cout << sc_time_stamp().to_string() << " PMIC BULK IN RAMPED down: " << (int)bulk_volt << std::endl;

    wait(5, SC_MS);
    addr_out.write(0);
    wrb_out.write(false);

    sc_stop();
}
