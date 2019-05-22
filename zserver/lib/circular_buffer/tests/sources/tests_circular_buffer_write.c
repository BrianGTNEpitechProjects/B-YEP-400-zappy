/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** tests_circular_buffer_write.c
*/

/* Created the 13/05/2019 at 17:27 by jfrabel */

#include <criterion/criterion.h>
#include "circular_buffer.h"

Test(circular_buffer_write, basic_write, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"thisIsAMessage\0An other one\n";

    cr_assert_eq(write_to_buffer(&c_buffer, to_write, 28), false);
    cr_assert_eq(c_buffer.read_pointer, 0);
    cr_assert_eq(c_buffer.write_pointer, 28);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 28);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(memcmp(to_write, c_buffer.buffer, 28), 0);
}

Test(circular_buffer_write, write_two_times, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"thisIsAMessage\0An other one\n";

    cr_assert_eq(write_to_buffer(&c_buffer, to_write, 28), false);
    cr_assert_eq(write_to_buffer(&c_buffer, to_write, 28), false);
    cr_assert_eq(c_buffer.read_pointer, 0);
    cr_assert_eq(c_buffer.write_pointer, 56);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 56);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(memcmp(to_write, c_buffer.buffer, 28), 0);
    cr_assert_eq(memcmp(to_write, c_buffer.buffer + 28, 28), 0);
}

Test(circular_buffer_write, write_overflow, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"this will overflow";

    c_buffer.read_pointer = 10;
    cr_assert_eq(write_to_buffer(&c_buffer, to_write, 18), true);
    cr_assert_eq(c_buffer.read_pointer, 18);
    cr_assert_eq(c_buffer.write_pointer, 18);
    cr_assert_eq(c_buffer.nb_buffered_bytes, C_BUFFER_SIZE);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, true);
    cr_assert_eq(memcmp(to_write, c_buffer.buffer, 18), 0);
}

Test(circular_buffer_write, write_overflow_too_long_input, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t to_write[C_BUFFER_SIZE + 4] = {0};

    cr_assert_eq(write_to_buffer(&c_buffer, to_write, C_BUFFER_SIZE + 4), true);
    cr_assert_eq(c_buffer.read_pointer, 4);
    cr_assert_eq(c_buffer.write_pointer, 4);
    cr_assert_eq(c_buffer.nb_buffered_bytes, C_BUFFER_SIZE);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, true);
}