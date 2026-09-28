#ifndef TIM2_HPP
#define TIM2_HPP

#include "registers.hpp"

class tim2_class{
public:
    void pwm_init(void);
    void pwm_set_duty_cycle(std::uint32_t, std::uint32_t, std::uint32_t);

private:
    struct tim2_pointers{
        register_class::vu32p cr1;
        register_class::vu32p sr;
        register_class::vu32p egr;
        register_class::vu32p ccmr1;
        register_class::vu32p ccmr2;
        register_class::vu32p ccer;
        register_class::vu32p cnt;
        register_class::vu32p psc;
        register_class::vu32p arr;
        register_class::vu32p ccr1;
        register_class::vu32p ccr2;
        register_class::vu32p ccr3;
    };
    
    inline static tim2_pointers tim2 = {
        .cr1    = register_class::reg32(register_class::base.tim2_base + 0x0u),
        .sr     = register_class::reg32(register_class::base.tim2_base + 0x10u),
        .egr    = register_class::reg32(register_class::base.tim2_base + 0x14u),
        .ccmr1  = register_class::reg32(register_class::base.tim2_base + 0x18u),
        .ccmr2  = register_class::reg32(register_class::base.tim2_base + 0x1cu),
        .ccer   = register_class::reg32(register_class::base.tim2_base + 0x20u),
        .cnt    = register_class::reg32(register_class::base.tim2_base + 0x24u),
        .psc    = register_class::reg32(register_class::base.tim2_base + 0x28u),
        .arr    = register_class::reg32(register_class::base.tim2_base + 0x2cu),
        .ccr1   = register_class::reg32(register_class::base.tim2_base + 0x34u),
        .ccr2   = register_class::reg32(register_class::base.tim2_base + 0x38u),
        .ccr3   = register_class::reg32(register_class::base.tim2_base + 0x3cu),
    };

    const std::uint32_t pwm_top = 999u;
};

#endif
