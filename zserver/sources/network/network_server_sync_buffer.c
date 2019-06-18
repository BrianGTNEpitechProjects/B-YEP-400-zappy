/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_sync_buffer.c
*/

/* Created the 21/05/2019 at 13:46 by jfrabel */

#include <stdio.h>
#include "network_server.h"

static void sync_client(network_client_t *client, fd_set *rfds, fd_set *wfds)
{
    if (FD_ISSET(client->socket, rfds)) {
        if (flush_socket_to_in(client)) {
            client->has_overflow = true;
        }
    }
    if (client->cb_out.nb_buffered_bytes != 0 &&
    FD_ISSET(client->socket, wfds)) {
        flush_out_to_socket(client);
    }
}

static void sync_batch(network_client_pool_batch_t *batch,fd_infos_t *infos)
{
    network_client_t *client;

    for (int i = 0; i < NETWORK_CLIENT_POOL_BATCH_SIZE; i++) {
        client = &batch->clients[i];
        if (client->socket != invalid_socket)
            sync_client(client, &infos->read_set, &infos->write_set);
    }
}

void sync_buffers(network_server_t *ns, fd_infos_t *infos)
{
    for (list_t curr = ns->client_pool->batches_list; curr; curr = curr->next) {
        sync_batch(curr->value, infos);
    }
}