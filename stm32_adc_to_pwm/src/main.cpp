#include "adc1.hpp"
#include "gpioa.hpp"
#include "gpiob.hpp"
#include "tim2.hpp"
#include "tim3.hpp"
#include "usart2.hpp"

int main(void){
    gpioa_class gpio_a;
    gpiob_class gpio_b;
    tim2_class tim_2;
    tim3_class tim_3;
    adc1_class adc1;
    usart2_class serial;

    gpio_a.init();
    gpio_b.init();
    tim_2.pwm_init();
    tim_3.init();
    adc1.init();
    serial.init();

    serial.write("\r\nUSART2 INITIALISED\r\n");
    std::uint32_t time_val_ms = 0u;

    while (true){
        auto values = adc1.read_sequence();

        std::uint32_t red_pct   = (values.sq1 * 100) / 4095;
        std::uint32_t green_pct = (values.sq2 * 100) / 4095;
        std::uint32_t blue_pct  = (values.sq3 * 100) / 4095;

        tim_2.pwm_set_duty_cycle(red_pct, green_pct, blue_pct); 
        if (tim_3.zero_point_one()){   
            serial.write_uint32_t(time_val_ms);
            serial.write_character(',');         
            serial.write_uint32_t(red_pct);
            serial.write_character(',');
            serial.write_uint32_t(values.sq1);
            serial.write_character(',');
            serial.write_uint32_t(green_pct);
            serial.write_character(',');
            serial.write_uint32_t(values.sq2);
            serial.write_character(',');
            serial.write_uint32_t(blue_pct);
            serial.write_character(',');
            serial.write_uint32_t(values.sq3);
            serial.write("\r\n");

            time_val_ms += 100;
        }
    }

    return 0;
}