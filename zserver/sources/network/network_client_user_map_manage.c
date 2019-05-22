/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_user_map_manage.c
*/

/* Created the 19/05/2019 at 21:37 by jfrabel */

#include <stdlib.h>
#include "network_client_user_map.h"

network_client_user_map_t *create_network_client_user_map(void)
{
    network_client_user_map_t *new_map = malloc(sizeof(*new_map));

    if (new_map != NULL) {
        new_map->client_user_map = EMPTY_MAP;
    }
    return (new_map);
}

void delete_network_client_user_map(network_client_user_map_t *map)
{
    if (map == NULL)
        return;
    map_clear(&map->client_user_map);
    free(map);
}

bool insert_client_in_map(network_client_user_map_t *map, network_client_t *c)
{
    return (map_add_elem(
        &map->client_user_map,
        c,
        NULL,
        (key_comparator_t)&network_client_cmp)
    );
}

void remove_client_from_map(network_client_user_map_t *m, network_client_t *c)
{
    if (m == NULL || c == NULL)
        return;
    map_del_elem(&m->client_user_map, c, (key_comparator_t)&network_client_cmp);
}