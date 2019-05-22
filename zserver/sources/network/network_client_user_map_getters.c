/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_user_map_getters.c
*/

/* Created the 19/05/2019 at 21:56 by jfrabel */

#include "network_client_user_map.h"

network_client_t *get_client(network_client_user_map_t *map, user_base_t *user)
{
    for (map_t curr = map->client_user_map; curr != NULL; curr = curr->next) {
        if (((client_user_pair_t *)curr->value)->user == user)
            return (((client_user_pair_t *)curr->value)->client);
    }
    return (NULL);
}

user_base_t *get_user(network_client_user_map_t *map, network_client_t *client)
{
    return (map_get_elem(
        map->client_user_map, client, (key_comparator_t)&network_client_cmp));
}