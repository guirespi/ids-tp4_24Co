#include <stdint.h>
#include <unity.h>

#include "led.h"

/**
 * @test Con la inicialización todos los LEDs quedan apagados.
 * @test Prender un LED individual.
 * @test Apagar un LED individual.
 * @test Prender y apagar múltiples LED’s.
 * @test Prender todos los LEDs de una vez.
 * @test Apagar todos los LEDs de una vez.
 * @test Consultar el estado de un LED que está encendido
 * @test Consultar el estado de un LED que est apagado
 * @test Revisar limites de los parametros.
 * @test Revisar parámetros fuera de los limites.
 */

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
    // Turn on all leds with previous tested function.
    led_turn_on_all();
    // Turn off all leds.
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

    // Turn on all leds with previous tested function.
    led_turn_on_all();
    // Turn it off just one led to check it later.
    led_turn_off(led_pos);

    TEST_ASSERT_EQUAL(false, led_is_on(led_pos));
}

//! @test Check off limits led to turn on and off
void test_check_off_limits_leds_for_turn_on_off(void) {
    uint8_t led_pos = 20;

    // Turn off all leds.
    led_turn_off_all();
    // Try to turn on an off limits led.
    led_turn_on(led_pos);

    TEST_ASSERT_EQUAL_HEX16(0x0000, led_address); // Check all are still off.

    // Turn on all valid leds.
    led_turn_on_all();
    // Try to turn off an off limits led.
    led_turn_off(led_pos);

    TEST_ASSERT_EQUAL_HEX16(0xFFFF, led_address); // Check all are still on.
}

//! @test Check off limits led to check state
void test_check_off_limits_leds_for_check_state(void) {
    uint8_t led_pos = 20;

    // Turn on all valid leds.
    led_turn_on_all();

    TEST_ASSERT_EQUAL(false, led_is_on(led_pos)); // Check if off limits led is off.

    // Turn off all valid leds.
    led_turn_off_all();
    // Try to turn on an off limits led.
    led_turn_on(led_pos);

    TEST_ASSERT_EQUAL(false, led_is_on(led_pos)); // Check if off limits led is off.
}

//! @test Check off limits led to check state
void test_check_null_led_register_for_init(void) {
    uint16_t * invalid_addr = NULL;

    // We do not allow null adress so the other functions don't commit ilegal access.
    led_init(invalid_addr);

    TEST_ASSERT_NOT_EQUAL(invalid_addr, &led_address);
}