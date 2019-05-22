/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** circular_buffer.h
*/

/* Created the 13/05/2019 at 11:12 by jfrabel */

#ifndef PSU_ZAPPY_2018_CIRCULAR_BUFFER_H
#define PSU_ZAPPY_2018_CIRCULAR_BUFFER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define C_BUFFER_SIZE (4096)
#define C_BUFFER_DEFAULT {0, 0, false, 0, {0}}

typedef struct circular_buffer_s {
    size_t read_pointer;
    size_t write_pointer;
    bool will_overflow_if_not_read;
    size_t nb_buffered_bytes;
    uint8_t buffer[C_BUFFER_SIZE];
} circular_buffer_t;

bool write_to_buffer(circular_buffer_t *buffer,
    const uint8_t *to_write, size_t size);
size_t read_from_buffer(circular_buffer_t *buffer,
    uint8_t *to_write, const uint8_t *delimiter, size_t delim_size);
size_t read_bytes_from_buffer(circular_buffer_t *buffer,
    uint8_t *to_write, size_t nb_bytes);
size_t flush_buffer(circular_buffer_t *buffer, uint8_t *to_write);
void clear_buffer(circular_buffer_t *buffer);

#endif //PSU_ZAPPY_2018_CIRCULAR_BUFFER_H
