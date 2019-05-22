/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_timeout_client.c
*/

/* Created the 21/05/2019 at 15:28 by jfrabel */

#include <stdio.h>
#include <time.h>
#include "network_manager.h"

void timeout_clients(network_manager_t *nm, time_t timeout_at)
{
    client_user_pair_t *pair;
    map_t curr = nm->client_user_map->client_user_map;
    time_t elapsed;

    if (timeout_at == 0)
        return;
    while (curr) {
        pair = curr->value;
        elapsed = time(NULL) - pair->client->last_data_in_timestamp;
        if (elapsed >= timeout_at || pair->client->lost_connection) {
            curr = curr->next;
            disconnect_client(nm, pair->client);
        } else {
            curr = curr->next;
        }
    }
}