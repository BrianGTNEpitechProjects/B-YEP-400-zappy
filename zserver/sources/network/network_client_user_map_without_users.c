/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_user_map_without_users.c
*/

/* Created the 19/05/2019 at 23:48 by jfrabel */

#include "network_client_user_map.h"

bool has_client_without_user(network_client_user_map_t *map)
{
    client_user_pair_t *pair;

    for (map_t curr = map->client_user_map; curr != NULL; curr = curr->next) {
        pair = curr->value;
        if (pair->user == NULL)
            return (true);
    }
    return (false);
}

client_user_pair_t *get_next_client_without_user(network_client_user_map_t \
*map)
{
    client_user_pair_t *pair;

    for (map_t curr = map->client_user_map; curr != NULL; curr = curr->next) {
        pair = curr->value;
        if (pair->user == NULL)
            return (pair);
    }
    return (NULL);
}