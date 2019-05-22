/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** tests_circular_buffer_empty.c
*/

/* Created the 13/05/2019 at 21:01 by jfrabel */

#include <criterion/criterion.h>
#include "circular_buffer.h"

Test(circular_buffer_empty, test, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;
    uint8_t *to_write = (uint8_t *)"thisIsAMessage\0An other one\0";

    write_to_buffer(&c_buffer, to_write, 28);
    clear_buffer(&c_buffer);
    cr_assert_eq(c_buffer.read_pointer, 0);
    cr_assert_eq(c_buffer.write_pointer, 0);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 0);
}

Test(circular_buffer_empty, empty_buffer, .timeout=10)
{
    circular_buffer_t c_buffer = C_BUFFER_DEFAULT;

    clear_buffer(&c_buffer);
    cr_assert_eq(c_buffer.read_pointer, 0);
    cr_assert_eq(c_buffer.write_pointer, 0);
    cr_assert_eq(c_buffer.will_overflow_if_not_read, false);
    cr_assert_eq(c_buffer.nb_buffered_bytes, 0);
}