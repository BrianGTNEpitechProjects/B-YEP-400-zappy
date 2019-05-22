/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_pool_infos.c
*/

/* Created the 19/05/2019 at 20:38 by jfrabel */

#include "network_client_pool.h"

size_t get_nb_slot_taken(const network_client_pool_t *pool)
{
    size_t tot = 0;
    network_client_t *client;

    for (list_t curr = pool->batches_list; curr != NULL; curr = curr->next) {
        for (int i = 0; i < NETWORK_CLIENT_POOL_BATCH_SIZE; i++) {
            client = &((network_client_pool_batch_t *)curr->value)->clients[i];
            tot += (client->socket != invalid_socket);
        }
    }
    return (tot);
}

size_t get_nb_slot_empty(const network_client_pool_t *pool)
{
    size_t tot = 0;
    network_client_t *client;

    for (list_t curr = pool->batches_list; curr != NULL; curr = curr->next) {
        for (int i = 0; i < NETWORK_CLIENT_POOL_BATCH_SIZE; i++) {
            client = &((network_client_pool_batch_t *)curr->value)->clients[i];
            tot += (client->socket == invalid_socket);
        }
    }
    return (tot);
}