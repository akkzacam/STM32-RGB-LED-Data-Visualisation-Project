#include "adc1.hpp"
#include "rcc.hpp"
#include "adc_common.hpp"

void adc1_class::init(void){
    register_class::set_bits<1>(*rcc.apb2enr, 0b1u, 8u);
    register_class::set_bits<2>(*adc_common.ccr, 0b10u, 16u);

    *adc1.cr1 = 0u;
    *adc1.cr2 = 0u;
    register_class::set_bits<1>(*adc1.cr1, 1u, 8u);   // SCAN mode
    register_class::set_bits<1>(*adc1.cr2, 1u, 10u);  // EOC after each conversion

    //set sampling rate for channels 0 -2 to 480 cycles, try out different cycles later if want faster
    register_class::set_bits<3>(*adc1.smpr2, 0b111u, adc1_channel_pointer->channel_0 * 3u);
    register_class::set_bits<3>(*adc1.smpr2, 0b111u, adc1_channel_pointer->channel_1 * 3u);
    register_class::set_bits<3>(*adc1.smpr2, 0b111u, adc1_channel_pointer->channel_4 * 3u);

    //set number of conversions in sqr1 to 3 conversions,
    //set conversion order is sqr3 to 0, clear
    register_class::set_bits<4>(*adc1.sqr1, 3u - 1u, 20u);
    register_class::set_bits<5>(*adc1.sqr3, adc1_channel_pointer->channel_0, 0u);
    register_class::set_bits<5>(*adc1.sqr3, adc1_channel_pointer->channel_1, 5u);
    register_class::set_bits<5>(*adc1.sqr3, adc1_channel_pointer->channel_4, 10u);

    //turn on adc via cr2
    register_class::set_bits<1>(*adc1.cr2, 0b1u, 0u);
}

adc1_class::sequence_slot adc1_class::read_sequence(void){
    sequence_slot sequence_slot_val = {};
    *adc1.sr = 0u;
    register_class::set_bits<1>(*adc1.cr2, 1u, 30u);

    while ((*adc1.sr & (0b1u << 1u)) == 0u){}
    sequence_slot_val.sq1 = *adc1.dr & 0x00000fffu;

    while ((*adc1.sr & (0b1u << 1u)) == 0u){}
    sequence_slot_val.sq2 = *adc1.dr & 0x00000fffu;

    while ((*adc1.sr & (0b1u << 1u)) == 0u){}
    sequence_slot_val.sq3 = *adc1.dr & 0x00000fffu;

    return sequence_slot_val;
}

