# pragma once
#include "Can.h"
#include <util/delay.h>
#include "math.h"

const uint8_t equivalenceDistanceChart[27] = { 
    174, 185, 184, 183, 172, 146, 129, 127,
    113, 109, 105, 97, 91, 87, 82, 78, 77,
    71, 68, 65, 62, 61, 58, 57, 56, 54, 53
    };

class DistanceCaptor {
public:
    DistanceCaptor();
    uint8_t readDistance();

private:
    uint8_t convertToCm(uint8_t analogicValue);
};
