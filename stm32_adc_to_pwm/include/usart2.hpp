#ifndef USART2_HPP
#define USART2_HPP

#include "registers.hpp"

class usart2_class{
public:
    void init(void);
    void write(const char *);
    void write_character(char);
    void write_uint32_t(std::uint32_t);

private:
    struct usart2_pointers{
        register_class::vu32p sr;
        register_class::vu32p dr;
        register_class::vu32p brr;
        register_class::vu32p cr1;
    };

    struct sr_bits{
        register_class::cu32 txe;
        register_class::cu32 rxne;
    };
    
    struct cr1_bits{
        register_class::cu32 re;
        register_class::cu32 te;
        register_class::cu32 ue;
    };

    struct monitor{
        register_class::cu32 clk_hz;
        register_class::cu32 baud_rate;
    };
    
    inline static usart2_pointers usart2 = {
        .sr     = register_class::reg32(register_class::base.usart2_base + 0x00u),
        .dr     = register_class::reg32(register_class::base.usart2_base + 0x04u),
        .brr    = register_class::reg32(register_class::base.usart2_base + 0x08u),
        .cr1    = register_class::reg32(register_class::base.usart2_base + 0x0cu)
    };
    
    const sr_bits sr_bits_vals = {
        .txe = 7u,
        .rxne = 5u
    };

    const cr1_bits cr1_bits_vals = {
        .re = 2u,
        .te = 3u,
        .ue = 13u
    };

    const monitor configurations = {
        .clk_hz = 16'000'000u,
        .baud_rate = 115'200u
    };

    const sr_bits *sr_bits_vals_pointer = &sr_bits_vals;
    const cr1_bits *cr1_bits_vals_pointer = &cr1_bits_vals;
    const monitor *configurations_pointer = &configurations;
};

#endif