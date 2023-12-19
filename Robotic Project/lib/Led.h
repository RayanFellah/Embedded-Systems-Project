#pragma once
#include <avr/io.h> 
#include <util/delay.h>

enum Color { Green, Red, Amber, Off };
const uint8_t GREEN_RATIO = 2;     // 1 sec of Green + 4 sec of Red = 5 sec of Amber
const uint8_t RED_RATIO = 3;       // Duration needs to be divided by 5,
const uint8_t AMBER_FACTOR = 5;    // when using "for" loops.
const uint8_t BLINK_DURATION = 100;

class Led {
public:
   Led();
   void setColor(Color color);
   void blink(Color color, uint8_t iteration = 1);
};
