/************************************************************************************************
Copyright (c) 2025, Guido Ramirez <guidoramirez7@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file led.c
 ** @brief Led's fucntions definition.
 **/

/* === Headers files inclusions =============================================================== */

#include <stdlib.h>
#include <led.h>

/* === Macros definitions ====================================================================== */

/**
 * @brief State representing all LEDs turned off.
 */
#define LED_STATE_ALL_OFF (0x0000)

/**
 * @brief State representing all LEDs turned on.
 */
#define LED_STATE_ALL_ON (0xFFFF)

/**
 * @brief Offset used to calculate the bit position of an LED.
 */
#define LED_TO_BIT_OFFSET (1)

/**
 * @brief Value representing an LED being turned on.
 */
#define LED_ON (1)

/**
 * @brief Macro to calculate the bitmask for a specific LED.
 *
 * @param led The position of the LED (1-based index).
 * @return The bitmask corresponding to the LED.
 */
#define LED_TO_MASK(led) (LED_ON << (led - LED_TO_BIT_OFFSET))

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Validates the port address.
 *
 * @return true if the port address is valid, false otherwise.
 */
static bool is_port_address_valid(void);

/**
 * @brief Validates the LED position.
 *
 * @param led_pos The position of the LED to validate.
 * @return true if the LED position is valid, false otherwise.
 */
static bool is_led_pos_valid(uint8_t led_pos);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/**
 * @brief Pointer to the LED register address.
 */
static uint16_t * port_address = NULL;

/* === Private function implementation ========================================================= */

static bool is_port_address_valid(void) {
    return (port_address != NULL);
}

static bool is_led_pos_valid(uint8_t led_pos) {
    return (led_pos > 0 && led_pos <= LED_MAX_POS);
}

/* === Public function implementation ========================================================== */

void led_init(uint16_t * led_reg) {
    if (led_reg == NULL)
        return;

    port_address = led_reg;
    *port_address = LED_STATE_ALL_OFF;
}

void led_turn_on(uint8_t led_pos) {
    if (!is_port_address_valid() || !is_led_pos_valid(led_pos))
        return;

    *port_address |= LED_TO_MASK(led_pos);
}

void led_turn_off(uint8_t led_pos) {
    if (!is_port_address_valid() || !is_led_pos_valid(led_pos))
        return;

    *port_address &= ~LED_TO_MASK(led_pos);
}

void led_turn_on_all(void) {
    if (!is_port_address_valid())
        return;

    *port_address = LED_STATE_ALL_ON;
}

void led_turn_off_all(void) {
    led_init(port_address);
}

bool led_is_on(uint8_t led_pos) {
    if (!is_port_address_valid() || !is_led_pos_valid(led_pos))
        return false;

    return (*port_address & LED_TO_MASK(led_pos));
}

/* === End of documentation ==================================================================== */