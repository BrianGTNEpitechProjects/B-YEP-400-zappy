/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** flush_buffer.c
*/

/* Created the 13/05/2019 at 20:40 by jfrabel */

#include "circular_buffer.h"

size_t flush_buffer(circular_buffer_t *buffer, uint8_t *to_write)
{
    size_t nb_bytes = buffer->nb_buffered_bytes;

    for (size_t i = 0; i < nb_bytes; i++) {
        to_write[i] = buffer->buffer[buffer->read_pointer];
        buffer->read_pointer = (buffer->read_pointer + 1) % C_BUFFER_SIZE;
    }
    buffer->nb_buffered_bytes = 0;
    return (nb_bytes);
}