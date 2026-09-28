#include "tim2.hpp"
#include "rcc.hpp"

void tim2_class::pwm_init(void){
    register_class::set_bits<1>(*rcc.apb1enr, 0b1u, 0u);

    *tim2.psc = 16u - 1u;
    *tim2.arr = pwm_top;

    *tim2.ccr1 = 0u;
    *tim2.ccr2 = 0u;
    *tim2.ccr3 = 0u;

    //channel 1
    //configure ccmr1.cc1s at bit 1:0 to 00 -> output mode
    //configure ccmr1.oc1m at bit 6:4 to 110 -> pwm mode 1
    //configure ccer.cc1e at bit 0 to 1 -> turn on output
    register_class::set_bits<2>(*tim2.ccmr1, 0b00u, 0u);
    register_class::set_bits<3>(*tim2.ccmr1, 0b110u, 4u);
    register_class::set_bits<1>(*tim2.ccer, 0b1u, 0u);

    //channel 2
    //configure ccmr1.cc2s at bit 9:8 to 00 -> output mode
    //configure ccmr1.oc2m at bit 14:12 to 110 -> pwm mode 1
    //configure ccer.cc1e at bit 4 to 1 -> turn on output
    register_class::set_bits<2>(*tim2.ccmr1, 0b00u, 8u);
    register_class::set_bits<3>(*tim2.ccmr1, 0b110u, 12u);
    register_class::set_bits<1>(*tim2.ccer, 0b1u, 4u);

    //channel 3
    //configure ccmr2.cc3s at bit 1:0 to 00 -> output mode
    //confiugre ccmr2.cc3m at bit 6:4 to 110 -> pwm mode 1
    //configure ccer.cc1e at bit 8 to 1 -> turn on output
    register_class::set_bits<2>(*tim2.ccmr2, 0b00u, 0u);
    register_class::set_bits<3>(*tim2.ccmr2, 0b110u, 4u);
    register_class::set_bits<1>(*tim2.ccer, 0b1u, 8u);

    //buffer tim2.arr via tim2.cr1 at bit 7
    //enable egr.ug at bit 0
    //start timer at tim2.cr1 at bit 0
    register_class::set_bits<1>(*tim2.cr1, 0b1u, 7u);
    register_class::set_bits<1>(*tim2.egr, 0b1u, 0u);
    register_class::set_bits<1>(*tim2.cr1, 0b1u, 0u);
}

void tim2_class::pwm_set_duty_cycle(
    std::uint32_t red_pct,
    std::uint32_t green_pct,
    std::uint32_t blue_pct){
    if (red_pct > 100){
        red_pct = 100u;
    }
    if (green_pct > 100){
        green_pct = 100u;
    }
    if (blue_pct > 100){
        blue_pct = 100u;
    }

    *tim2.ccr1 = ((pwm_top + 1u) * red_pct) / 100u;
    *tim2.ccr2 = ((pwm_top + 1u) * green_pct) / 100u;
    *tim2.ccr3 = ((pwm_top + 1u) * blue_pct) / 100u;
}