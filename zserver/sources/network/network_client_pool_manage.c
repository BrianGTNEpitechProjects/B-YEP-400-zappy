/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_pool_manage.c
*/

/* Created the 19/05/2019 at 20:46 by jfrabel */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "network_client_pool.h"

network_client_pool_t *create_new_pool()
{
    network_client_pool_t *new_pool = malloc(sizeof(*new_pool));

    if (new_pool != NULL) {
        new_pool->nb_batch = 0;
        new_pool->batches_list = EMPTY_LIST;
    }
    return (new_pool);
}

void delete_pool(network_client_pool_t *pool)
{
    if (pool == NULL)
        return;
    for (list_t curr = pool->batches_list; curr != NULL; curr = curr->next) {
        delete_batch((network_client_pool_batch_t *)curr->value);
    }
    list_clear(&pool->batches_list);
    free(pool);
}

bool add_new_batch(network_client_pool_t *pool)
{
    network_client_t client = NETWORK_CLIENT_DEFAULT;
    network_client_pool_batch_t *new_batch;

    if (pool == NULL)
        return (false);
    new_batch = malloc(sizeof(*new_batch));
    if (new_batch == NULL)
        return (false);
    for (int i = 0; i < NETWORK_CLIENT_POOL_BATCH_SIZE; i++) {
        memcpy(&new_batch->clients[i], &client, sizeof(client));
    }
    if (!list_add_elem_at_front(&pool->batches_list, new_batch)) {
        free(new_batch);
        return (false);
    }
    return (true);
}

void delete_batch(network_client_pool_batch_t *batch)
{
    if (batch == NULL)
        return;
    for (int i = 0; i < NETWORK_CLIENT_POOL_BATCH_SIZE; i++) {
        if (batch->clients[i].socket != invalid_socket)
            close(batch->clients[i].socket);
    }
    free(batch);
}