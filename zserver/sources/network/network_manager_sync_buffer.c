/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_sync_buffer.c
*/

/* Created the 21/05/2019 at 13:46 by jfrabel */

#include <stdio.h>
#include "network_manager.h"

static void sync_client(network_client_t *client, fd_set *rfds, fd_set *wfds)
{
    if (FD_ISSET(client->socket, rfds)) {
        if (flush_socket_to_in(client)) {
            fprintf(stderr, "WARNING: circular buffer override, data lost\n");
        }
    }
    if (FD_ISSET(client->socket, wfds)) {
        flush_out_to_socket(client);
    }
}

static void sync_batch(network_client_pool_batch_t *batch)
{
    int biggest_socket = invalid_socket;
    fd_set read_set;
    fd_set write_set;
    struct timeval to = {0, 1};

    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    for (int i = 0; i < NETWORK_CLIENT_POOL_BATCH_SIZE; i++) {
        if (batch->clients[i].socket == invalid_socket)
            continue;
        if (batch->clients[i].socket > biggest_socket)
            biggest_socket = batch->clients[i].socket;
        FD_SET(batch->clients[i].socket, &read_set);
        FD_SET(batch->clients[i].socket, &write_set);
    }
    if (biggest_socket == invalid_socket)
        return;
    if (select(biggest_socket + 1, &read_set, &write_set, NULL, &to) > 0)
        for (int i = 0; i < NETWORK_CLIENT_POOL_BATCH_SIZE; i++)
            sync_client(&batch->clients[i], &read_set, &write_set);
}

void sync_buffers(network_manager_t *nm)
{
    for (list_t curr = nm->client_pool->batches_list; curr; curr = curr->next) {
        sync_batch(curr->value);
    }
}