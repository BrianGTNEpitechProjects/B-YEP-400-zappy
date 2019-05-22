/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_pool_getters.c
*/

/* Created the 19/05/2019 at 21:05 by jfrabel */

#include "network_client_pool.h"

static network_client_t *get_client_batch(
    network_client_pool_batch_t *batch,
    int sock)
{
    for (int i = 0; i < NETWORK_CLIENT_POOL_BATCH_SIZE; i++) {
        if (batch->clients[i].socket == sock)
            return (&batch->clients[i]);
    }
    return (NULL);
}

network_client_t *get_empty_client(network_client_pool_t *pool)
{
    network_client_t *found = NULL;

    found = get_client_with_socket(pool, invalid_socket);
    if (found)
        return (found);
    if (add_new_batch(pool)) {
        return (get_client_batch(pool->batches_list->value, invalid_socket));
    }
    return (NULL);
}

network_client_t *get_client_with_socket(network_client_pool_t *pool, int sock)
{
    network_client_t *found = NULL;

    for (list_t curr = pool->batches_list; curr != NULL; curr = curr->next) {
        found = get_client_batch(curr->value, sock);
        if (found)
            return (found);
    }
    return (NULL);
}