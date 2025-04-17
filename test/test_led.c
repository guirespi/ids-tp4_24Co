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

/**
 * @file test_led.c
 * @brief Unit tests for the LED module.
 */

/* === Headers files inclusions =============================================================== */

#include "led.h"
#include "unity.h"

/* === Macros definitions ====================================================================== */

/**
 * @brief Invalid LED position above the maximum allowed value.
 *
 * This macro represents an out-of-bounds LED position that is greater than
 * the maximum valid LED position (`LED_MAX_POS`).
 */
#define INVALID_LED_POS_TOP (LED_MAX_POS + 1)

/**
 * @brief Invalid LED position below the minimum allowed value.
 */
#define INVALID_LED_POS_BOTTOM (0)

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/**
 * @brief Test led address value and register.
 */
static uint16_t led_address = 0xFFFF;

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void setUp(void) {
    led_init(&led_address);
}

//! @test All initialized leds are turn off.
void test_all_leds_initialized_start_off(void) {
    uint16_t led_address = 0xFFFF;

    led_err_t rt = led_init(&led_address);
    TEST_ASSERT_EQUAL(LED_OK, rt);
    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address);
}

//! @test Turn on a single led.
void test_turn_on_single_led(void) {
    uint8_t led_pos = 4;

    led_turn_on(led_pos);

    TEST_ASSERT_EQUAL_HEX16((1 << (led_pos - 1)), led_address);
}

//! @test Turn off a single led.
void test_turn_off_single_led(void) {
    uint8_t led_pos = 4;

    led_turn_on(led_pos);
    led_turn_off(led_pos);

    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address);
}

//! @test Turn on/off multple leds.
void test_turn_on_off_multiple_led(void) {

    led_turn_on(2);
    led_turn_on(8);
    led_turn_on(10);

    TEST_ASSERT_EQUAL_HEX16((1 << (2 - 1)) | (1 << (8 - 1)) | (1 << (10 - 1)), led_address);

    led_turn_off(2);
    led_turn_off(8);
    led_turn_off(10);

    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address);
}

//! @test Turn on all leds.
void test_turn_on_all_leds(void) {

    led_turn_on_all();

    TEST_ASSERT_EQUAL_HEX16(0xFFFF, led_address);
}

//! @test Turn off all leds.
void test_turn_off_all_leds(void) {

    led_turn_on_all();
    led_turn_off_all();

    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address);
}

//! @test Check a turn on led state.
void test_check_turn_on_led(void) {
    uint8_t led_pos = 3;

    led_turn_on(led_pos);

    TEST_ASSERT_EQUAL(true, led_is_on(led_pos));
}

//! @test Check a turn off led state.
void test_check_turn_off_led(void) {
    uint8_t led_pos = 5;

    led_turn_on_all();
    led_turn_off(led_pos);

    TEST_ASSERT_EQUAL(false, led_is_on(led_pos));
}

//! @test Check off limits led to turn on and off
void test_check_off_limits_leds_for_turn_on_off(void) {

    led_turn_off_all();

    led_turn_on(INVALID_LED_POS_TOP);
    led_turn_on(INVALID_LED_POS_BOTTOM);

    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address);

    led_turn_on_all();

    led_turn_off(INVALID_LED_POS_TOP);
    led_turn_off(INVALID_LED_POS_BOTTOM);

    TEST_ASSERT_EQUAL_HEX16(0xFFFF, led_address);
}

//! @test Check off limits led to check state
void test_check_off_limits_leds_for_check_state(void) {

    led_turn_on_all();

    TEST_ASSERT_EQUAL(false, led_is_on(INVALID_LED_POS_TOP));
    TEST_ASSERT_EQUAL(false, led_is_on(INVALID_LED_POS_BOTTOM));

    led_turn_off_all();

    led_turn_on(INVALID_LED_POS_TOP);
    led_turn_on(INVALID_LED_POS_BOTTOM);

    TEST_ASSERT_EQUAL(false, led_is_on(INVALID_LED_POS_TOP));
    TEST_ASSERT_EQUAL(false, led_is_on(INVALID_LED_POS_BOTTOM));
}

//! @test Check off limits led to check state
void test_check_null_led_register_for_init(void) {
    uint16_t * invalid_addr = NULL;

    // We do not allow null adress so the other functions don't commit ilegal access.
    led_err_t rt = led_init(invalid_addr);

    TEST_ASSERT_EQUAL(LED_E_ARG, rt);
}

void test_check_led_deinit(void) {
    led_turn_on_all();
    led_deinit();

    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address);
}

/* === End of documentation ==================================================================== */