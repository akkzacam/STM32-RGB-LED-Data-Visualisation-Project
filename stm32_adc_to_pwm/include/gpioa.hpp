#ifndef GPIOA_HPP
#define GPIOA_HPP

#include "registers.hpp"
#include "rcc.hpp"

class gpioa_class{
    public:
        void init(void);

    private:
        struct gpioa_pointers{
            register_class::vu32p moder;
            register_class::vu32p pupdr;
            register_class::vu32p afrl;
        };

        struct pin_a_locations{
            register_class::cu32 pa0;
            register_class::cu32 pa1;
            register_class::cu32 pa2;
            register_class::cu32 pa3;
            register_class::cu32 pa4;
            register_class::cu32 pa5;
        };

        inline static gpioa_pointers gpioa = {
            .moder  = register_class::reg32(register_class::base.gpioa_base + 0x00u),
            .pupdr  = register_class::reg32(register_class::base.gpioa_base + 0x0cu),
            .afrl   = register_class::reg32(register_class::base.gpioa_base + 0x20u)
        };

        const pin_a_locations pin_a = {
            .pa0 = 0u,
            .pa1 = 1u,
            .pa2 = 2u,
            .pa3 = 3u,
            .pa4 = 4u,
            .pa5 = 5u
        };

        const pin_a_locations *pin_a_pointer = &pin_a;
};

#endif