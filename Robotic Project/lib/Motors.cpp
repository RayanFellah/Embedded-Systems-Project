#include "Motors.h"
Motors::Motors() {
    DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);
}

void Motors::setVelocity(uint8_t velocityLeft, uint8_t velocityRight) {
    if (velocityLeft == 0) {
        stopLeft();
    }
    else { 
        moveForwardLeft(velocityLeft);
    }

    if (velocityRight == 0) {
        stopRight();
    }
    else { 
        moveForwardRight(velocityRight);
    }
}

void Motors::moveForwardRight(uint8_t velocityRight) {
    OCR0B = velocityRight;
    TCCR0A |= (1 << WGM00) | (1 << COM0B1);
    TCCR0A &= ~(1 << COM0B0);
    TCCR0B |= (1 << CS01);
    DDRB |= (1 << PB4);
    PORTB &= ~(1 << PB5);
}

void Motors::moveBackwardRight(uint8_t velocityRight) {
    OCR0B = velocityRight;
    TCCR0A |= (1 << WGM00) | (1 << COM0B1);
    TCCR0A &= ~(1 << COM0B0);
    TCCR0B |= (1 << CS01);
    DDRB |= (1 << PB4) | (1 << PB5);
    PORTB |= (1 << PB5);
}

void Motors::moveForwardLeft(uint8_t velocityLeft) {
    OCR0A = velocityLeft;
    TCCR0A |= (1 << WGM00) | (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);
    TCCR0B |= (1 << CS01);
    DDRB |= (1 << PB3);
    PORTB &= ~(1 << PB2);
}

void Motors::moveBackwardLeft(uint8_t velocityLeft) {
    OCR0A = velocityLeft;
    TCCR0A |= (1 << WGM00) | (1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);
    TCCR0B |= (1 << CS01);
    DDRB |= (1 << PB2) | (1 << PB3);
    PORTB |= (1 << PB2);
}

void Motors::stopLeft() {
    OCR0A = 0;
}

void Motors::stopRight() {
    OCR0B = 0;
}

void Motors::stopMotors() {
    stopLeft();
    stopRight();
}
