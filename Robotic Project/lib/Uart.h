#pragma once
#include <avr/io.h>
#include "memoire_24.h"

class Uart {
public:
    Uart();
    uint8_t receiveByte();
    void transferByte(uint8_t data);
};