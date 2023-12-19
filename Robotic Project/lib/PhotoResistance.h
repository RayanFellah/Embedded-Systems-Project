#pragma once
#include "Can.h"
#include "Led.h"
const uint16_t ITERATIONS = 250;
const uint8_t UNCERTAINTY = 10; 

class PhotoResistance {
public:
   PhotoResistance();
   uint8_t readValue(uint8_t pin);

   uint8_t getRight() { return averageRightLight_; }
   uint8_t getLeft() { return averageRightLight_; }

private:
   uint8_t averageRightLight_ = 0;
   uint8_t averageLeftLight_ = 0;
};
