#include "memoire_24.h"
#include <util/delay.h>
#include <avr/interrupt.h>

class Memory {
public:
    void recordStep(uint8_t velocityLeft, uint8_t velocityRight);
    uint8_t readStep();
    bool isReading(uint16_t counter);
    void saveCounter();
    uint16_t loadCounter();
    uint16_t getAddress() { return writingAddress_; }

private:
    uint8_t readData_;
    Memoire24CXXX mem_;
    uint16_t writingAddress_ = 2;
    uint16_t readAddress_ = 0;
};