#include "Uart.h"

Uart::Uart() {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

uint8_t Uart::receiveByte() {
    while(!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void Uart::transferByte(uint8_t data) {
    while ( !(UCSR0A & (1 << UDRE0)) );
    UDR0 = data;
}