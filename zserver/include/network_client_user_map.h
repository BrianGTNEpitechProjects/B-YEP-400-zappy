/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_user_map.h
*/

/* Created the 16/05/2019 at 15:29 by jfrabel */

#ifndef PSU_ZAPPY_2018_NETWORK_CLIENT_USER_MAP_H
#define PSU_ZAPPY_2018_NETWORK_CLIENT_USER_MAP_H

#include "network_user_base.h"
#include "network_client.h"
#include "map.h"

struct network_server_s;

typedef struct network_client_user_map_s {
    map_t client_user_map;
} network_client_user_map_t;

typedef struct client_user_pair_s {
    network_client_t *client;
    user_base_t *user;
} client_user_pair_t;

network_client_user_map_t *create_network_client_user_map(void);
void delete_network_client_user_map(network_client_user_map_t *map);

bool insert_client_in_map(network_client_user_map_t *map, network_client_t *c);
void remove_client_from_map(network_client_user_map_t *m, network_client_t *c);

network_client_t *get_client(network_client_user_map_t *map, user_base_t *user);
user_base_t *get_user(network_client_user_map_t *map, network_client_t *client);

bool has_client_without_user(network_client_user_map_t *map);
client_user_pair_t *get_next_client_without_user(network_client_user_map_t *m);

#endif //PSU_ZAPPY_2018_NETWORK_CLIENT_USER_MAP_H
