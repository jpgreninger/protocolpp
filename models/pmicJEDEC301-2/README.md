# JEDEC301-2-1 PMIC SystemC model

Model for this PMIC spec

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
