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

#ifndef LED_H
#define LED_H

/** @file led.h
 ** @brief Led's functions declaration.
 **/

/* === Headers files inclusions ================================================================ */

#include <stdint.h>
#include <stdbool.h>

/* === C++ header ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/**
 * @brief Maximum position of the LEDs (0-based index).
 */
#define LED_MAX_POS (16)

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Initialize the led's register.
 *
 * @param led_reg Led's register address.
 */
void led_init(uint16_t * led_reg);

/**
 * @brief Turns on a specific LED.
 *
 * @param led_pos The position of the LED to turn on (1-based index).
 */
void led_turn_on(uint8_t led_pos);

/**
 * @brief Turns off a specific LED.
 *
 * @param led_pos The position of the LED to turn off (1-based index).
 */
void led_turn_off(uint8_t led_pos);

/**
 * @brief Turns on all LEDs.
 */
void led_turn_on_all(void);

/**
 * @brief Turns off all LEDs.
 */
void led_turn_off_all(void);

/**
 * @brief Checks if a specific LED is on.
 *
 * @param led_pos The position of the LED to check (1-based index).
 * @return true if the LED is on, false otherwise.
 */
bool led_is_on(uint8_t led_pos);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* LED_H */