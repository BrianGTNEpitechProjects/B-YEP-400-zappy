/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** clear_buffer.c
*/

/* Created the 13/05/2019 at 20:39 by jfrabel */

#include "circular_buffer.h"

void clear_buffer(circular_buffer_t *buffer)
{
    buffer->nb_buffered_bytes = 0;
    buffer->read_pointer = 0;
    buffer->write_pointer = 0;
    buffer->will_overflow_if_not_read = false;
}