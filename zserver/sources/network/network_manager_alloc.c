/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_alloc.c
*/

/* Created the 03/06/2019 at 21:33 by jfrabel */

#include <stdlib.h>
#include "network_manager.h"

network_manager_t *create_manager(void)
{
    network_manager_t *nm = malloc(sizeof(*nm));

    if (nm) {
        nm->biggest_id = invalid_id;
        nm->nb_servers = 0;
        nm->servers = EMPTY_LIST;
        nm->timeout_on_stdin = false;
    }
    return (nm);
}

void delete_manager(network_manager_t *nm)
{
    for (list_t curr = nm->servers; curr != EMPTY_LIST; curr = curr->next) {
        delete_server(curr->value);
    }
    list_clear(&nm->servers);
    free(nm);
}