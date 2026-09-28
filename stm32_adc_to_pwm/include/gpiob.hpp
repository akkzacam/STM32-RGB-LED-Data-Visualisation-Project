#ifndef GPIOB_HPP
#define GPIOB_HPP

#include "registers.hpp"
#include "rcc.hpp"

class gpiob_class{
    public:
    void init(void);

    private:
    struct gpiob_pointers{
        register_class::vu32p moder;
        register_class::vu32p afrl;
        register_class::vu32p afrh;
    };

    struct pin_b_locations{
        register_class::cu32 pb3;
        register_class::cu32 pb10;
    };

    inline static gpiob_pointers gpiob = {
        .moder  = register_class::reg32(register_class::base.gpiob_base + 0x00u),
        .afrl   = register_class::reg32(register_class::base.gpiob_base + 0x20u),
        .afrh   = register_class::reg32(register_class::base.gpiob_base + 0x24u)
    };

    const pin_b_locations pin_b = {
        .pb3    = 3u,
        .pb10   = 10u
    };

    const pin_b_locations *pin_b_pointers = &pin_b;
};

#endif