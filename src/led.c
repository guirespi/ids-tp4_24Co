#include <stdlib.h>
#include <led.h>

#define LED_MAX_POS (16)

static uint16_t * port_address = NULL;

void led_init(uint16_t * led_reg) {
    if (led_reg == NULL)
        return;

    port_address = led_reg;
    *port_address = 0x0000;
}

void led_turn_on(uint8_t led_pos) {
    if (port_address == NULL)
        return;
    if (led_pos >= LED_MAX_POS)
        return;

    *port_address |= (1 << led_pos);
}

void led_turn_off(uint8_t led_pos) {
    if (port_address == NULL)
        return;
    if (led_pos >= LED_MAX_POS)
        return;

    *port_address &= ~(1 << led_pos);
}