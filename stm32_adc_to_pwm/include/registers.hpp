#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <cstdint>

class register_class{
    public:
    using vu32p = volatile std::uint32_t *;
    using cu32  = const std::uint32_t;

    template<std::uint32_t bit_width> inline static void set_bits(
        volatile std::uint32_t &register_address_content,
        std::uint32_t set_val,
        std::uint32_t location
    ){
        static_assert(bit_width >= 1u && bit_width <= 31u);
        cu32 field_mask = (0b1u << bit_width) - 1u;
        cu32 mask = field_mask << location;
        register_address_content = (register_address_content & ~mask) | ((set_val & field_mask) << location);
    }

    static vu32p reg32(std::uint32_t register_address_location){
        return reinterpret_cast<vu32p>(register_address_location);
    }

    struct base_registers{
        cu32 rcc_base;
        cu32 gpioa_base;
        cu32 gpiob_base;
        cu32 tim2_base;
        cu32 tim3_base;
        cu32 usart2_base;
        cu32 adc1_base;
        cu32 adc_common;
    };

    inline static const base_registers base = {
        .rcc_base       = 0x40023800u,
        .gpioa_base     = 0x40020000u,
        .gpiob_base     = 0x40020400u,
        .tim2_base      = 0x40000000u,
        .tim3_base      = 0x40000400u,
        .usart2_base    = 0x40004400u,
        .adc1_base      = 0x40012000u,
        .adc_common     = 0x40012300u    
    };
};

#endif