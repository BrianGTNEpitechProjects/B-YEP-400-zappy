/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_flush.c
*/

/* Created the 15/05/2019 at 17:07 by jfrabel */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "network_client.h"

bool flush_socket_to_in(network_client_t *client)
{
    uint8_t tmp_buff[C_BUFFER_SIZE] = {0};
    ssize_t bytes_readed = read(client->socket, tmp_buff, C_BUFFER_SIZE);

    if (bytes_readed == -1)
        perror("flush_socket_to_in read");
    if (bytes_readed <= 0) {
        client->lost_connection = 1;
        return (false);
    }
    client->last_data_in_timestamp = time(NULL);
    return (write_to_buffer(&client->cb_in, tmp_buff, bytes_readed));
}

void flush_out_to_socket(network_client_t *client)
{
    uint8_t tmp[C_BUFFER_SIZE];
    size_t bytes_flushed = flush_buffer(&client->cb_out, tmp);
    size_t bytes_written = write(client->socket, tmp, bytes_flushed);
    size_t bytes_failed = bytes_flushed - bytes_written;

    if (bytes_written == (size_t)-1) {
        write_to_buffer(&client->cb_out, tmp, bytes_flushed);
        return;
    }
    if (bytes_failed != 0) {
        write_to_buffer(&client->cb_out, tmp + bytes_written, bytes_failed);
    }
    client->last_data_out_timestamp = time(NULL);
}