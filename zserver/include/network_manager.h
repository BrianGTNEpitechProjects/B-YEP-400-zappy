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

#define TOZ(to) (to.tv_usec == 0 && to.tv_sec == 0)
#define TOZN(to) ((to.tv_usec == 0 && to.tv_sec == 0) || \
to.tv_usec < 0 || to.tv_sec < 0)
#define TOLT(to1, to2) ((to1.tv_sec < to2.tv_sec) || \
(to1.tv_sec == to2.tv_sec && to1.tv_usec < to2.tv_usec))
#define TOGT(to1, to2) ((to1.tv_sec > to2.tv_sec) || \
(to1.tv_sec == to2.tv_sec && to1.tv_usec > to2.tv_usec))

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
