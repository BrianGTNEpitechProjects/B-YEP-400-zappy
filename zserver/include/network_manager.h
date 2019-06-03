/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager.h
*/

/* Created the 03/06/2019 at 21:12 by jfrabel */

#ifndef PSU_ZAPPY_2018_NETWORK_MANAGER_H
#define PSU_ZAPPY_2018_NETWORK_MANAGER_H

#include "generic_list.h"
#include "network_server.h"

typedef unsigned int id_t;

extern const id_t invalid_id;

typedef struct network_manager_s {
    id_t biggest_id;
    int nb_servers;
    list_t servers;
    bool timeout_on_stdin;
} network_manager_t;

network_manager_t *create_manager(void);
void delete_manager(network_manager_t *nm);

bool update_manager(network_manager_t *nm);

id_t add_server(network_manager_t *nm, int port);
void remove_server(network_manager_t *nm, id_t server_id);
network_server_t *get_server(network_manager_t *nm, id_t server_id);

#endif //PSU_ZAPPY_2018_NETWORK_MANAGER_H
