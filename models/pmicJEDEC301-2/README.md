# JEDEC301-2-1 PMIC SystemC model

Basic model for this PMIC spec. I have often been accused of being too "fancy" because I implement all the features and every detail, so I have limited the model to the default functionality as expressed in the default settings of the registers and in the diagrams of the spec. See chapter 6 for the basic functionalty. Most status registers are not updated except for rail PG, Table 102-203, and the ADC outputs. The ADC is fully functional and the I2c/I3C interface has been turned into a simple C++ read/write with wrb strobe. Missing functionality that may or may not be implemented in the future

* Error injection
* Programmable mode single rail on/off
* PWRGD and GSI_n full functionality (see the multiple charts in the GSI_n section, by default they are both disabled)

Functionality that will be added in the future:

* Fault detection for OVM/UVM/OCM/UCM/BULK and temperature

If you would like a fully functional SystemC model of this spec, you can find it in the paid version of Protocolpp®

Rail configuratin to support the soft_start/stop idle times and soft_start/stop times for rails requires adding the ramp time to the idle time for the correct effect. For example, using the default values, the soft_start_time is 1ms with an idle of 2ms. To get the staggered rails ramp of D-B-A, add the ramp time of D to the idle time of B, etc. Here's an example from jrail::railcfg

    std::vector<jrail::railcfg> railcfg;
    railcfg.emplace_back(1100, 0.275, 6000, 4000, 24000, 1100, 2200, 5000, 0);
    railcfg.emplace_back(1100, 0.275, 6000, 4000, 24000, 1100, 2200, 3000, 500);
    railcfg.emplace_back(1800, 1.800, 6000, 2000, 12000, 1800, 1800, 0, 1000);

RailB idle time is 2ms+1ms or 3ms. RailA idle time is 6000 due to the ramp time of 1m for RailB and 2ms idle time before RailA starts to ramp up. Rail configuration structure is found below

    struct railcfg {
        int voltage;
        float resistance;
        int max_volt;
        int max_current;
        int max_power;
        int slewup;
        int slewdn;
        int slewupdly;
        int slewdndly;

        railcfg(int volt,
                float res,
                int maxv,
                int maxc,
                int maxp,
                int sup,
                int sdn,
                int upd,
                int dnd) : voltage(volt),
                           resistance(res),
                           max_volt(maxv),
                           max_current(maxc),
                           max_power(maxp),
                           slewup(sup),
                           slewdn(sdn),
                           slewupdly(upd),
                           slewdndly(dnd) {}
    };

Thanks
