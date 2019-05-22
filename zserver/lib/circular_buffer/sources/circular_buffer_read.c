/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** circular_buffer_read.c
*/

/* Created the 13/05/2019 at 15:25 by jfrabel */

#include <string.h>
#include "circular_buffer.h"

#include <stdio.h>
static int c_strcmp(const uint8_t buff[C_BUFFER_SIZE],
    const size_t start_pos, const uint8_t *delim, size_t delim_size)
{
    for (size_t i = 0; i < delim_size; i++) {
        if (delim[i] != buff[(start_pos + i) % C_BUFFER_SIZE]) {
            return (delim[i] - buff[(start_pos + i) % C_BUFFER_SIZE]);
        }
    }
    return (0);
}

static size_t find_delimiter(const circular_buffer_t *buffer,
    const uint8_t *delim, size_t delim_size)
{
    size_t nb_iterations = buffer->nb_buffered_bytes - delim_size + 1;
    size_t pos_in_buffer = buffer->read_pointer;

    if (buffer->nb_buffered_bytes < delim_size)
        return (-1);
    for (size_t i = 0; i < nb_iterations; i++) {
        if (c_strcmp(buffer->buffer, pos_in_buffer, delim, delim_size) == 0) {
            return (i + delim_size);
        }
        pos_in_buffer++;
    }
    return (-1);
}

static void extract_from_buffer(circular_buffer_t *buff,
    uint8_t *to_write, size_t nb_bytes_to_extract)
{
    for (size_t i = 0; i < nb_bytes_to_extract; i++) {
        to_write[i] = buff->buffer[buff->read_pointer];
        buff->read_pointer = (buff->read_pointer + 1) % C_BUFFER_SIZE;
    }
    buff->nb_buffered_bytes -= nb_bytes_to_extract;
}

size_t read_from_buffer(circular_buffer_t *buffer,
    uint8_t *to_write, const uint8_t *delim, size_t delim_size)
{
    size_t nb_bytes_to_extract = find_delimiter(buffer, delim, delim_size);

    if (nb_bytes_to_extract == (size_t)(-1))
        return (-1);
    extract_from_buffer(buffer, to_write, nb_bytes_to_extract);
    return (nb_bytes_to_extract);
}
