/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager.h
*/

/* Created the 15/05/2019 at 16:30 by jfrabel */

#ifndef PSU_ZAPPY_2018_NETWORK_MANAGER_H
#define PSU_ZAPPY_2018_NETWORK_MANAGER_H

#define MAX_PENDING_CONNECTIONS 10

#define PRINT_DEBUG 1

#include "network_user_base.h"
#include "network_client_pool.h"
#include "network_client_user_map.h"

typedef struct network_manager_s network_manager_t;

struct network_manager_s {
    int connexion_socket;
    struct sockaddr_in addr;
    network_client_pool_t *client_pool;
    network_client_user_map_t *client_user_map;
};

void disconnect_client(network_manager_t *nm, network_client_t *client);
void disconnect_user(network_manager_t *nm, user_base_t *user);

int accept_connections(network_manager_t *nm);
void sync_buffers(network_manager_t *nm);
void extract_to_users(network_manager_t *nm, uint8_t *delim, size_t delim_size);
void timeout_clients(network_manager_t *nm, time_t timeout_at);
void update_manager(network_manager_t *nm,
    uint8_t *delim, size_t delim_size, time_t timeout_at);

network_manager_t *create_manager(int port);
void delete_manager(network_manager_t *nm);

#endif //PSU_ZAPPY_2018_NETWORK_MANAGER_H
