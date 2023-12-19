#include "Robot.h"

Robot::Robot() {}

bool Robot::verifyLight() {
    uint8_t rightRead = photoResistance_.readValue(PA6);
    uint8_t leftRead = photoResistance_.readValue(PA7);
    if (rightRead >= photoResistance_.getRight() + UNCERTAINTY || 
        leftRead >= photoResistance_.getLeft() + UNCERTAINTY) {
        return true;
    }
    return false;
}

void Robot::followLight() {
    uint8_t rightRead = photoResistance_.readValue(PA6);
    uint8_t leftRead = photoResistance_.readValue(PA7);

    uint8_t percentageRight = ((double(rightRead)/photoResistance_.getRight()) * PERCENT);
    uint8_t percentageLeft = ((double(leftRead)/photoResistance_.getLeft()) * PERCENT);

    // Percentage from [0, 200], at 100+, it means that there's light intensivity gain.
    percentageRight = (percentageRight < (PERCENT + UNCERTAINTY)) ? PERCENT : percentageRight;
    percentageLeft = (percentageLeft < (PERCENT + UNCERTAINTY)) ? PERCENT : percentageLeft;

    percentageRight = (percentageRight > 200) ? 200 : percentageRight;
    percentageLeft = (percentageLeft > 200) ? 200 : percentageLeft;

    // Moving a specific motor will invert the robot's orientation.
    uint8_t rightMotor = 0;
    uint8_t leftMotor = 0;

    if (percentageRight >= (PERCENT + UNCERTAINTY)) {
        //motors_.moveForwardLeft(155 + percentageRight - 100);
        leftMotor = MINIMUM_PWM + percentageRight - PERCENT;
    }

    if (percentageLeft >= (PERCENT + UNCERTAINTY)) {
        //motors_.moveForwardRight(155 + percentageLeft - 100);
        rightMotor = MINIMUM_PWM + percentageLeft - PERCENT;
    }
    motors_.setVelocity(leftMotor, rightMotor);
    writeMemory(leftMotor, rightMotor);
}

bool Robot::detectWall() {
    //_delay_ms(30);
    uint8_t distance = distanceCaptor_.readDistance();
    if (distance <= 25 && distance >= 5)
        return true;
    return false;
}

// The U-TURN needs to be completed
bool Robot::findNewWall() {
    if (distanceCaptor_.readDistance() <= 20)
        return true;
    return false;
}


void Robot::followWall() {
    while (detectWall()) {
        uint8_t rightMotor = MINIMUM_PWM;
        uint8_t leftMotor = MINIMUM_PWM;
        uint8_t distance = distanceCaptor_.readDistance();
        uart_.transferByte(distance);
        if (distance <= 24 && distance > 21) {
            leftMotor += DIFFERENCE_PWM;
        }
        else if (distance >= 5 && distance < 19) { 
            rightMotor += DIFFERENCE_PWM;
        }
        motors_.setVelocity(leftMotor, rightMotor);
        writeMemory(leftMotor, rightMotor);
    }

    motors_.setVelocity(0, 0);
    writeMemory(0, 0);
}

void Robot::performUTurn() {
    // motors_.setVelocity(250, 250);
    // _delay_ms(500);
    while (!findNewWall()) {
        led_.setColor(Amber);
        motors_.moveForwardLeft(230);
        motors_.moveForwardRight(170);
    }

    motors_.stopMotors();
    led_.setColor(Off);
};

void Robot::writeMemory(uint8_t velocityLeft, uint8_t velocityRight) {
    if (gRecordMemory) {
        memory_.recordStep(velocityLeft, velocityRight);
        _delay_ms(100);
    }
}

void Robot::readMemory() {
    uint16_t counter = memory_.loadCounter();
    while (memory_.isReading(counter)) {
        uint8_t velocityLeft = memory_.readStep();
        uint8_t velocityRight = memory_.readStep();
        motors_.setVelocity(velocityLeft, velocityRight);
        _delay_ms(100);
    }
    motors_.stopMotors();
}

void Robot::testButton() {
    while(true) {
        if (!buttons_.debounce(3)) {
            led_.setColor(Green);
            _delay_ms(2000);
        }

        led_.setColor(Off);
    }
}

void Robot::testMotors() {
    motors_.moveForwardLeft(200);
    _delay_ms(2000);
    motors_.stopLeft();
    _delay_ms(2000);
}

void Robot::testPhotoResistance() {
    while (true) {
        uint8_t rightRead = photoResistance_.readValue(PA6);
        uint8_t percentageRight = ((double(rightRead)/photoResistance_.getRight()) * PERCENT);
        percentageRight = (percentageRight < (PERCENT + UNCERTAINTY)) ? PERCENT : percentageRight;
        percentageRight = (percentageRight > 200) ? 200 : percentageRight;
        uart_.transferByte(percentageRight);
    }
    while (true) {
        uint8_t rightRead = photoResistance_.readValue(PA6);
        uint8_t percentageRight = ((double(rightRead)/photoResistance_.getRight()) * PERCENT);
        percentageRight = (percentageRight < (PERCENT + UNCERTAINTY)) ? PERCENT : percentageRight;
        uart_.transferByte(percentageRight);
    }
}

void Robot::testDistanceCaptor() {
    while (true) {
        _delay_ms(5);
        uint8_t mesure = distanceCaptor_.readDistance();
        uart_.transferByte(mesure);
    }
}

void Robot::executeParkour() {
    while (true) {
        switch (gCurrentState) {
            case State::INIT:
                // This case performs the one with memory.
                if (!buttons_.debounce(PD3)) {
                    led_.blink(Red, 15);
                    gCurrentState = State::REDO_PARKOUR;
                }
                else if (buttons_.debounce(PD2)) {
                    led_.blink(Green, 15);
                    gCurrentState = State::START_PARKOUR;
                }
                break;

            case State::START_PARKOUR:
                followWall();
                gCurrentState = State::AWAIT;
                break;

            case State::AWAIT:
                led_.setColor(Green);
                if (!buttons_.debounce(PD3)) {
                    performUTurn();
                    gRecordMemory = false;
                    gCurrentState = State::START_PARKOUR;
                }
                else if (buttons_.debounce(PD2)) {
                    gCurrentState = State::WRITE_MEMORY;
                }
                else if (verifyLight()) {
                    gCurrentState = State::FOLLOW_LIGHT;
                }
                break;

            case State::FOLLOW_LIGHT:
                led_.setColor(Red);
                while (!detectWall()) {
                    followLight();
                }
                gCurrentState = State::START_PARKOUR;
                break;

            case State::WRITE_MEMORY:
                led_.setColor(Red);
                uart_.transferByte(memory_.getAddress());
                uart_.transferByte(memory_.getAddress() >> 8);
                uart_.transferByte(memory_.getAddress() << 8);
                memory_.saveCounter();
                _delay_ms(2000);
                gCurrentState = State::FINISHED;
                break;
            
            case State::REDO_PARKOUR:
                readMemory();
                gCurrentState = State::FINISHED;
                break;
            
            case State::FINISHED:
                led_.setColor(Green);
                break;
        }
    }
}
