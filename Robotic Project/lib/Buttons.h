#pragma once
#include <avr/io.h>
#include <util/delay.h>

const uint8_t DEBOUNCE_TIME = 10;

class Buttons {
public:
   Buttons();
   bool debounce(uint8_t pin);
};
