/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** circular_buffer.c
*/

/* Created the 13/05/2019 at 14:27 by jfrabel */

#include "circular_buffer.h"

static bool write_char_to_buffer(circular_buffer_t *buffer, uint8_t c)
{
    bool overflowed = buffer->will_overflow_if_not_read;

    buffer->buffer[buffer->write_pointer] = c;
    buffer->write_pointer = (buffer->write_pointer + 1) % C_BUFFER_SIZE;
    if (overflowed) {
        buffer->read_pointer = buffer->write_pointer;
        buffer->nb_buffered_bytes = C_BUFFER_SIZE;
    } else {
        buffer->nb_buffered_bytes++;
    }
    if (buffer->write_pointer == buffer->read_pointer) {
        buffer->will_overflow_if_not_read = true;
    }
    return (overflowed);
}

bool write_to_buffer(circular_buffer_t *buffer,
    const uint8_t *to_write, size_t size)
{
    bool overflowed = false;

    for (size_t i = 0; i < size; i++) {
        overflowed = write_char_to_buffer(buffer, to_write[i]) || overflowed;
    }
    return (overflowed);
}