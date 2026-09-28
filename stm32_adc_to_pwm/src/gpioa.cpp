#include "gpioa.hpp"
#include "rcc.hpp"

void gpioa_class::init(void){
    register_class::set_bits<1>(*rcc.ahb1enr, 0b1u, 0b0u);

    //set pa0, 1, 4 to analogue mode for adc1 and then set to no pupd
    register_class::set_bits<2>(*gpioa.moder, 0b11u, pin_a_pointer->pa0 * 2);
    register_class::set_bits<2>(*gpioa.moder, 0b11u, pin_a_pointer->pa1 * 2);
    register_class::set_bits<2>(*gpioa.moder, 0b11u, pin_a_pointer->pa4 * 2);
    register_class::set_bits<2>(*gpioa.pupdr, 0b00u, pin_a_pointer->pa0 * 2);
    register_class::set_bits<2>(*gpioa.pupdr, 0b00u, pin_a_pointer->pa1 * 2);
    register_class::set_bits<2>(*gpioa.pupdr, 0b00u, pin_a_pointer->pa4 * 2);

    //set pa5 to afrl1 tim2
    register_class::set_bits<2>(*gpioa.moder, 0b10u, pin_a_pointer->pa5 * 2);
    register_class::set_bits<4>(*gpioa.afrl, 1u, pin_a_pointer->pa5 * 4);

    //set pa2 and pa3 to afrl7 usart2
    register_class::set_bits<2>(*gpioa.moder, 0b10u, pin_a_pointer->pa2 * 2);
    register_class::set_bits<2>(*gpioa.moder, 0b10u, pin_a_pointer->pa3 * 2);
    register_class::set_bits<4>(*gpioa.afrl, 7u, pin_a_pointer->pa2 * 4);
    register_class::set_bits<4>(*gpioa.afrl, 7u, pin_a_pointer->pa3 * 4);
}