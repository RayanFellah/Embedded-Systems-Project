#pragma once
#include <avr/io.h>
#include <util/delay.h>

const uint8_t MINIMUM_PWM = 155;
const uint8_t MAX_PWM = 255;
const uint8_t AVERAGE_PWM = 175;
const uint8_t DIFFERENCE_PWM = 30;
const uint8_t PERCENT = 100;

static volatile bool gRecordMemory = true;

class Motors {
public:
    Motors();
    void setVelocity(uint8_t velocityLeft, uint8_t velocityRight);
    void moveForwardRight(uint8_t velocityRight);
    void moveBackwardRight(uint8_t velocityRight);
    void moveForwardLeft(uint8_t velocityLeft);
    void moveBackwardLeft(uint8_t velocityLeft);
    
    void stopLeft();
    void stopRight();
    void stopMotors();

private:
};
