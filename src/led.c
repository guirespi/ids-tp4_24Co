#include <stdlib.h>
#include <led.h>

#define LED_MAX_POS       (16)
#define LED_STATE_ALL_OFF (0x0000)
#define LED_STATE_ALL_ON  (0xFFFF)
#define LED_TO_BIT_OFFSET (1)
#define LED_ON            (1)

#define LED_TO_MASK(led)  (LED_ON << (led - LED_TO_BIT_OFFSET))

static uint16_t * port_address = NULL;

void led_init(uint16_t * led_reg) {
    if (led_reg == NULL)
        return;

    port_address = led_reg;
    *port_address = LED_STATE_ALL_OFF;
}

void led_turn_on(uint8_t led_pos) {
    if (port_address == NULL)
        return;
    if (led_pos > LED_MAX_POS)
        return;

    *port_address |= LED_TO_MASK(led_pos);
}

void led_turn_off(uint8_t led_pos) {
    if (port_address == NULL)
        return;
    if (led_pos > LED_MAX_POS)
        return;

    *port_address &= ~LED_TO_MASK(led_pos);
}

void led_turn_on_all(void) {
    if (port_address == NULL)
        return;
    *port_address = LED_STATE_ALL_ON;
}

void led_turn_off_all(void) {
    led_init(port_address);
}

bool led_is_on(uint8_t led_pos) {
    if (port_address == NULL)
        return false;
    if (led_pos > LED_MAX_POS)
        return false;

    return (*port_address & LED_TO_MASK(led_pos));
}