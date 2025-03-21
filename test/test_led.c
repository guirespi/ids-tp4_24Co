#include <stdint.h>
#include <unity.h>

#include "led.h"

static uint16_t led_address = 0xffff;

void setUp(void) {
    led_init(&led_address);
}

void tearDown(void) {
    ;
}

//! @test All initialized leds are turn off.
void test_all_leds_initialized_start_off(void) {
    uint16_t led_address = 0xFFFF;

    led_init(&led_address);
    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address);
}

//! @test Turn on a single led.
void test_turn_on_single_led(void) {
    uint8_t led_pos = 4;

    led_turn_on(led_pos);

    TEST_ASSERT_EQUAL_HEX16((1 << led_pos), led_address);
}

//! @test Turn off a single led.
void test_turn_off_single_led(void) {
    uint8_t led_pos = 4;

    led_turn_on(led_pos);
    led_turn_off(led_pos);

    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address);
}