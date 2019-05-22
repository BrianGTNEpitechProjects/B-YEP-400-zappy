/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** tests_circular_buffer_read_bytes.c
*/

/* Created the 13/05/2019 at 20:42 by jfrabel */

#include <criterion/criterion.h>
#include "circular_buffer.h"

Test(circular_buffer_read_bytes, basic_read, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"thisIsAMessage\0An other one\0";
    uint8_t read_buffer[C_BUFFER_SIZE] = {0};

    write_to_buffer(&c_buffer, to_write, 28);
    cr_assert_eq(read_bytes_from_buffer(&c_buffer, read_buffer, 15), 15);
    cr_assert_eq(c_buffer.read_pointer, 15);
    cr_assert_eq(c_buffer.write_pointer, 28);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 13);
    cr_assert_eq(memcmp(read_buffer, to_write, 15), 0);
}

Test(circular_buffer_read_bytes, two_reads, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"thisIsAMessage\0An other one\0";
    uint8_t read_buffer[C_BUFFER_SIZE] = {0};

    write_to_buffer(&c_buffer, to_write, 28);
    cr_assert_eq(read_bytes_from_buffer(&c_buffer, read_buffer, 15), 15);
    cr_assert_eq(c_buffer.read_pointer, 15);
    cr_assert_eq(c_buffer.write_pointer, 28);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 13);
    cr_assert_eq(memcmp(read_buffer, to_write, 15), 0);
    cr_assert_eq(read_bytes_from_buffer(&c_buffer, read_buffer, 13), 13);
    cr_assert_eq(c_buffer.read_pointer, 28);
    cr_assert_eq(c_buffer.write_pointer, 28);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 0);
    cr_assert_eq(memcmp(read_buffer, to_write + 15, 13), 0);
}

Test(circular_buffer_read_bytes, to_big_read, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"thisIsAMessage\0An other one\0";
    uint8_t read_buffer[C_BUFFER_SIZE] = {0};

    write_to_buffer(&c_buffer, to_write, 28);
    cr_assert(read_bytes_from_buffer(&c_buffer, read_buffer, 99) == (size_t)-1);
    cr_assert_eq(c_buffer.read_pointer, 0);
    cr_assert_eq(c_buffer.write_pointer, 28);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 28);
}

Test(circular_buffer_read_bytes, pointer_order_reversed, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"123456";
    uint8_t read_buffer[C_BUFFER_SIZE] = {0};

    c_buffer.read_pointer = 15;
    c_buffer.write_pointer = 5;
    c_buffer.nb_buffered_bytes = C_BUFFER_SIZE - 10;
    memcpy(&c_buffer.buffer[c_buffer.read_pointer], to_write, 6);
    cr_assert_eq(read_bytes_from_buffer(&c_buffer, read_buffer, 5), 5);
    cr_assert_eq(c_buffer.read_pointer, 20);
    cr_assert_eq(c_buffer.write_pointer, 5);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, C_BUFFER_SIZE - 10 - 5);
    cr_assert_eq(memcmp(read_buffer, to_write, 5), 0);
}

Test(circular_buffer_read_bytes, empty_buffer_zero_bytes, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t read_buffer[C_BUFFER_SIZE] = {0};

    cr_assert_eq(read_bytes_from_buffer(&c_buffer, read_buffer, 0), 0);
    cr_assert_eq(c_buffer.read_pointer, 0);
    cr_assert_eq(c_buffer.write_pointer, 0);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 0);
}