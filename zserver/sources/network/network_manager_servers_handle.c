/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_servers_handle.c
*/

/* Created the 03/06/2019 at 21:40 by jfrabel */

#include "network_manager.h"

id_t add_server(network_manager_t *nm, int port)
{
    id_t new_id = (++(nm->biggest_id));
    network_server_t *server = create_server(port, new_id);

    if (server != NULL && list_add_elem_at_front(&nm->servers, server)) {
        nm->nb_servers++;
    } else {
        delete_server(server);
        nm->biggest_id--;
        new_id = invalid_id;
    }
    return (new_id);
}

void remove_server(network_manager_t *nm, id_t server_id)
{
    network_server_t *server;

    for (list_t curr = nm->servers; curr != EMPTY_LIST; curr = curr->next) {
        server = curr->value;
        if (server->id == server_id) {
            delete_server(server);
            list_del_node(&nm->servers, curr);
            return;
        }
    }
}

network_server_t *get_server(network_manager_t *nm, id_t server_id)
{
    network_server_t *server;

    for (list_t curr = nm->servers; curr != EMPTY_LIST; curr = curr->next) {
        server = curr->value;
        if (server->id == server_id) {
            return (server);
        }
    }
    return (NULL);
}