#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void led_init(uint16_t * led_reg);
void led_turn_on(uint8_t led_pos);
void led_turn_off(uint8_t led_pos);
void led_turn_on_all(void);
void led_turn_off_all(void);
bool led_is_on(uint8_t led_pos);

#ifdef __cplusplus
}
#endif

#endif /* LED_H */