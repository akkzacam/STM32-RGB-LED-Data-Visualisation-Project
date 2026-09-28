#ifndef ADC_COMMON_HPP
#define ADC_COMMON_HPP

#include "registers.hpp"

struct adc_ccr{
    register_class::vu32p ccr;
};

inline adc_ccr adc_common = {.ccr = register_class::reg32(register_class::base.adc_common + 0x04u)};

#endif