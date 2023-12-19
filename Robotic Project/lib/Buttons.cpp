#include "Buttons.h"

Buttons::Buttons() {
  DDRD &= ~((1 << PD2) | (1 << PD3));
}

bool Buttons::debounce(uint8_t pin) {
    if (PIND & (1 << pin)) {
        _delay_ms(DEBOUNCE_TIME);          // Delay of the debounce.
        if (PIND & (1 << pin))
            return true;
    }
    
    return false;
}
