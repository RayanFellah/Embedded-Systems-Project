#include "Memory.h"

void Memory::recordStep(uint8_t velocityLeft, uint8_t velocityRight) {
    mem_.ecriture(writingAddress_, velocityLeft);
    _delay_ms(5);
    writingAddress_++;
    mem_.ecriture(writingAddress_, velocityRight);
    _delay_ms(5);
    writingAddress_++;
}

uint8_t Memory::readStep() {
    mem_.lecture(readAddress_, &readData_);
    _delay_ms(5);
    readAddress_++;
    return readData_;
}

bool Memory::isReading(uint16_t counter) {
    return (readAddress_ <= counter);
}

void Memory::saveCounter() {
    mem_.ecriture(0, uint8_t(writingAddress_ >> 8));
    _delay_ms(5);
    mem_.ecriture(1, uint8_t(writingAddress_));
    _delay_ms(5);
}

uint16_t Memory::loadCounter() {
    uint16_t firstByte = (uint16_t(readStep())) << 8;
    uint16_t secondByte = uint16_t(readStep());
    return firstByte | secondByte;
}
