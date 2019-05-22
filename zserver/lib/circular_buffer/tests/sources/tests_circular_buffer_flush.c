/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** tests_circular_buffer_flush.c
*/

/* Created the 13/05/2019 at 20:48 by jfrabel */

#include <criterion/criterion.h>
#include "circular_buffer.h"

Test(circular_buffer_flush, basic, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"thisIsAMessage\0An other one\0";
    uint8_t read_buffer[C_BUFFER_SIZE] = {0};

    write_to_buffer(&c_buffer, to_write, 28);
    cr_assert_eq(flush_buffer(&c_buffer, read_buffer), 28);
    cr_assert_eq(c_buffer.read_pointer, 28);
    cr_assert_eq(c_buffer.write_pointer, 28);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 0);
    cr_assert_eq(memcmp(read_buffer, to_write, 28), 0);
}

Test(circular_buffer_flush, reversed_order, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"123456";
    uint8_t read_buffer[C_BUFFER_SIZE] = {0};

    c_buffer.read_pointer = 15;
    c_buffer.write_pointer = 5;
    c_buffer.nb_buffered_bytes = C_BUFFER_SIZE - 10;
    memcpy(&c_buffer.buffer[c_buffer.read_pointer], to_write, 6);
    cr_assert_eq(flush_buffer(&c_buffer, read_buffer), C_BUFFER_SIZE - 10);
    cr_assert_eq(c_buffer.read_pointer, 5);
    cr_assert_eq(c_buffer.write_pointer, 5);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 0);
    cr_assert_eq(memcmp(read_buffer, to_write, 6), 0);
}

Test(circular_buffer_flush, empty_buffer, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t read_buffer[C_BUFFER_SIZE] = {0};

    cr_assert_eq(flush_buffer(&c_buffer, read_buffer), 0);
    cr_assert_eq(c_buffer.read_pointer, 0);
    cr_assert_eq(c_buffer.write_pointer, 0);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 0);
}