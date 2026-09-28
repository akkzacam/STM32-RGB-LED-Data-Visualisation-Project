#include <cstddef>
#include "usart2.hpp"
#include "rcc.hpp"

void usart2_class::init(void){
    register_class::set_bits<1>(*rcc.apb1enr, 0b1u, 17u);
    *usart2.brr = (configurations_pointer->clk_hz + (configurations_pointer->baud_rate / 2)) / configurations_pointer->baud_rate;
    register_class::set_bits<1>(*usart2.cr1, 0b1u, cr1_bits_vals_pointer->re);
    register_class::set_bits<1>(*usart2.cr1, 0b1u, cr1_bits_vals_pointer->te);
    register_class::set_bits<1>(*usart2.cr1, 0b1u, cr1_bits_vals_pointer->ue);
};

void usart2_class::write(const char *text){
    for (std::size_t i = 0u; text[i] != '\0'; i++){
        write_character(text[i]);
    }
}

void usart2_class::write_character(char character){
    while((*usart2.sr & (0b1u << sr_bits_vals_pointer->txe)) == 0u){}
    *usart2.dr = static_cast<std::uint32_t>(character);
}

void usart2_class::write_uint32_t(std::uint32_t val){
    std::size_t i = 0u;
    char digits[10];

    if (val == 0u){
        write_character('0');
        return;
    }

    for (; val != 0u; i++){
        digits[i] = static_cast<char>('0' + (val % 10));
        val /= 10;
    }

    for (; i != 0u; i--){
        write_character(digits[i - 1]);
    }
}
