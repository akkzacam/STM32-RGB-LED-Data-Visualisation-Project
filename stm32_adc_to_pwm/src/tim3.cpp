#include "tim3.hpp"
#include "rcc.hpp"

void tim3_class::init(void){
    register_class::set_bits<1>(*rcc.apb1enr, 0b1u, 1u);
    *tim3.psc = 1599u;
    *tim3.arr = 999u;
    register_class::set_bits<1>(*tim3.egr, 0b1u, 0u);
    *tim3.cnt = 0u;
    *tim3.sr = 0u;
    register_class::set_bits<1>(*tim3.cr1, 0b1u, 0u);
}

bool tim3_class::zero_point_one(void){
    if((*tim3.sr & 1u) != 0u){
        *tim3.sr = 0u;
        return true;
    }
    else{
        return false;
    }
}