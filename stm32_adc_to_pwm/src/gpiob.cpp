#include "gpiob.hpp"
#include "rcc.hpp"

void gpiob_class::init(void){
    register_class::set_bits<1>(*rcc.ahb1enr, 0b1u, 1u);
    
    //set pb3 and pb10 to afrl1 tim2
    register_class::set_bits<2>(*gpiob.moder, 0b10u, pin_b_pointers->pb3 * 2);
    register_class::set_bits<2>(*gpiob.moder, 0b10u, pin_b_pointers->pb10 * 2);
    register_class::set_bits<4>(*gpiob.afrl, 1u, pin_b_pointers->pb3 * 4);
    register_class::set_bits<4>(*gpiob.afrh, 1u, (pin_b_pointers->pb10 - 8u) * 4);
}