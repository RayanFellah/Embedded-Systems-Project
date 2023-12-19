#include "DistanceCaptor.h"

DistanceCaptor::DistanceCaptor() {
    DDRA &= ~(1 << PA4);
}

// This method has been worked experimentally.
uint8_t DistanceCaptor::convertToCm(uint8_t analogicValue) {
    uint8_t comparator = fabs(analogicValue - equivalenceDistanceChart[0]);
    uint8_t valueInCm = 4;
    for (int i = 0; i < 27; ++i) {
        if (fabs(analogicValue - equivalenceDistanceChart[i]) < comparator) {
            comparator = fabs(analogicValue - equivalenceDistanceChart[i]);
            valueInCm = i + 4;
        }
    }

    return valueInCm;
}

uint8_t DistanceCaptor::readDistance() {
    Can readCan;
    uint8_t distance = uint8_t(readCan.lecture(PA4) >> 2);
    return convertToCm(distance);
}