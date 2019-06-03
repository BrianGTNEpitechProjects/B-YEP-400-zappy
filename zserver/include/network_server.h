/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager.h
*/

/* Created the 15/05/2019 at 16:30 by jfrabel */

#ifndef PSU_ZAPPY_2018_NETWORK_SERVER_H
#define PSU_ZAPPY_2018_NETWORK_SERVER_H

#define MAX_PENDING_CONNECTIONS 10

#define PRINT_DEBUG 1

#include "network_user_base.h"
#include "network_client_pool.h"
#include "network_client_user_map.h"
#include "fd_infos.h"

typedef struct network_server_s network_server_t;

struct network_server_s {
    id_t id;
    int connexion_socket;
    struct sockaddr_in addr;
    time_t world_event_timeout;
    time_t default_client_disconnect_timeout;
    network_client_pool_t *client_pool;
    network_client_user_map_t *client_user_map;
};

void disconnect_client(network_server_t *ns, network_client_t *client);
void disconnect_user(network_server_t *ns, user_base_t *user);

int accept_connections(network_server_t *ns, fd_infos_t *infos);
void sync_buffers(network_server_t *ns, fd_infos_t *infos);
void update_disconnected(network_server_t *ns);
void update_server(network_server_t *ns, fd_infos_t *infos);

void extract_to_users(network_server_t *ns, uint8_t *delim, size_t delim_size);

network_server_t *create_server(int port, id_t id);
void delete_server(network_server_t *ns);

#endif //PSU_ZAPPY_2018_NETWORK_SERVER_H
