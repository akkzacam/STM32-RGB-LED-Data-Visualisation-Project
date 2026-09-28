#ifndef RCC_HPP
#define RCC_HPP

#include "registers.hpp"

struct rcc_pointers{
    register_class::vu32p ahb1enr;
    register_class::vu32p apb1enr;
    register_class::vu32p apb2enr;
};

inline rcc_pointers rcc = {
    .ahb1enr = register_class::reg32(register_class::base.rcc_base + 0x30u),
    .apb1enr = register_class::reg32(register_class::base.rcc_base + 0x40u),
    .apb2enr = register_class::reg32(register_class::base.rcc_base + 0x44u)
};

#endif