#ifndef ADC1_HPP
#define ADC1_HPP

#include "registers.hpp"

class adc1_class{
    public:
        void init(void);

        struct sequence_slot{
            std::uint32_t sq1;
            std::uint32_t sq2;
            std::uint32_t sq3;
        };

        sequence_slot read_sequence(void);

    private:
        struct adc1_pointers{
            register_class::vu32p sr;
            register_class::vu32p cr1;
            register_class::vu32p cr2;
            register_class::vu32p smpr2;
            register_class::vu32p sqr1;
            register_class::vu32p sqr3;
            register_class::vu32p dr;
        };
        
        struct channel_val{
            register_class::cu32 channel_0;
            register_class::cu32 channel_1;
            register_class::cu32 channel_4;
        };
        
        inline static adc1_pointers adc1 = {
            .sr     = register_class::reg32(register_class::base.adc1_base + 0x00u),
            .cr1    = register_class::reg32(register_class::base.adc1_base + 0x04u),
            .cr2    = register_class::reg32(register_class::base.adc1_base + 0x08u),
            .smpr2  = register_class::reg32(register_class::base.adc1_base + 0x10u),
            .sqr1   = register_class::reg32(register_class::base.adc1_base + 0x2cu),
            .sqr3   = register_class::reg32(register_class::base.adc1_base + 0x34u),
            .dr     = register_class::reg32(register_class::base.adc1_base + 0x4cu)
        };
        
        const channel_val adc1_channel = {
            .channel_0 = 0u,
            .channel_1 = 1u,
            .channel_4 = 4u
        };
        
        const channel_val *adc1_channel_pointer = &adc1_channel;
};

#endif