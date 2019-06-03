/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** client_pool.h
*/

/* Created the 15/05/2019 at 13:11 by jfrabel */

#ifndef PSU_ZAPPY_2018_NETWORK_CLIENT_POOL_H
#define PSU_ZAPPY_2018_NETWORK_CLIENT_POOL_H

#include "generic_list.h"
#include "network_client.h"

#define NETWORK_CLIENT_POOL_BATCH_SIZE (10)

#define CLIENT_POOL_BATCH_DEFAULT {{NETWORK_CLIENT_DEFAULT}}
#define CLIENT_POOL_DEFAULT {0, LIST_DEFAULT}

typedef struct network_client_pool_batch_s {
    network_client_t clients[NETWORK_CLIENT_POOL_BATCH_SIZE];
} network_client_pool_batch_t;

typedef struct network_client_pool_s {
    size_t nb_batch;
    list_t batches_list;
} network_client_pool_t;

size_t get_nb_slot_taken(const network_client_pool_t *pool);
size_t get_nb_slot_empty(const network_client_pool_t *pool);

network_client_pool_t *create_new_pool(void);
void delete_pool(network_client_pool_t *pool);
void delete_batch(network_client_pool_batch_t *batch);

bool add_new_batch(network_client_pool_t *pool);

network_client_t *get_empty_client(network_client_pool_t *pool);
network_client_t *get_client_with_socket(network_client_pool_t *pool, int sock);

#endif //PSU_ZAPPY_2018_NETWORK_CLIENT_POOL_H
